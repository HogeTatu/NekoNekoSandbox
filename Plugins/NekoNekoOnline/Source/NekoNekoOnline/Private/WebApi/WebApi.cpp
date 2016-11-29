#include "NekoNekoOnlinePrivatePCH.h"
#include "Request/WebApiRequestBodyUrlParam.h"
#include "Response/WebApiResponseBodyString.h"
#include "Response/WebApiResponseBodyBinary.h"
#include "Filter/WebApiRequestFilterInterface.h"
#include "Filter/WebApiRequestFilterBlueprintInterface.h"
#include "Filter/WebApiResponseFilterInterface.h"
#include "Filter/WebApiResponseFilterBlueprintInterface.h"
#include "WebApi.h"

UWebApi::UWebApi(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, bIsProcessingRequest(false)
{
	SuccessResponseCodes.Add(EHttpResponseCodes::Ok);
	ResponseClass = UWebApiResponseBodyString::StaticClass();
}

UWebApi* UWebApi::Create(UObject* WorldContext, TSubclassOf<UWebApi> ApiClass)
{
	return NewObject<UWebApi>(WorldContext, ApiClass);
}

FString UWebApi::GenerateUrl()
{
	FString Url;

	for (const auto& UrlElement : UrlElements)
	{
		Url += UrlElement;
	}

	return Url;
}

bool UWebApi::ProcessRequest(UWebApiRequestBody* InRequest, const TArray<UObject*>& InRequestFilters, const TArray<UObject*>& InResponseFilters)
{
	FScopeLock ScopeLock(&SyncObject);

	if(bIsProcessingRequest)
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("Request is processing already."));
		return false;
	}

	UWebApiRequestBody* Request = InRequest;
	ProcessingRequestFilters = InRequestFilters;
	ProcessingResponseFilters = InResponseFilters;

	// フィルタリング
	for (auto FilterObject : ProcessingRequestFilters)
	{
		if (auto RequestFilter = Cast<IWebApiRequestFilterInterface>(FilterObject))
		{
			Request = RequestFilter->ExecuteRequestFilter(Request);
		}
		else if (FilterObject->GetClass()->ImplementsInterface(UWebApiRequestFilterBlueprintInterface::StaticClass()))
		{
			Request = IWebApiRequestFilterBlueprintInterface::Execute_ExecuteRequestFilter(FilterObject, Request);
		}
	}

	auto& Module = FHttpModule::Get();
	ProcessingRequest = Module.CreateRequest();
	{
		ProcessingRequest->SetVerb(Request->GetRequestTypeAsString());
		ProcessingRequest->OnProcessRequestComplete().BindUObject(this, &UWebApi::OnRequestCompletedInternal);
		ProcessingRequest->OnRequestProgress().BindUObject(this, &UWebApi::OnRequestProgressInternal);
	}

	// URL、リクエストコンテンツ設定
	FString Url = GenerateUrl();
	if (Request->GetRequestType() == EWebApiRequestType::Get)
	{
		auto RequestAsUrlParam = Cast<UWebApiRequestBodyUrlParam>(Request);
		if (RequestAsUrlParam)
		{
			FString RequestParamString;
			if (RequestAsUrlParam->GetRequestBodyAsString(RequestParamString) && RequestParamString.Len() > 0)
			{
				ProcessingRequest->SetURL(Url + TEXT("?") + RequestParamString);
			}
			else
			{
				ProcessingRequest->SetURL(Url);
			}
		}
		else
		{
			UE_LOG(LogNekoNekoOnline, Warning, TEXT("EWebApiRequestType::Get support only UWebApiRequestBodyUrlParam."));
			ProcessingRequest->SetURL(Url);
		}
	}
	else
	{
		ProcessingRequest->SetURL(Url);

		do {
			FString RequestContentString;
			if (Request->GetRequestBodyAsString(RequestContentString))
			{
				if (RequestContentString.Len() > 0)
				{
					ProcessingRequest->SetContentAsString(RequestContentString);
				}
				break;
			}

			TArray<uint8> RequestContentBytes;
			if (Request->GetRequestBodyAsBinary(RequestContentBytes))
			{
				if (RequestContentBytes.Num() > 0)
				{
					ProcessingRequest->SetContent(RequestContentBytes);
				}
				break;
			}
		} while (false);
	}

	// ヘッダー設定
	Request->SetDefaultRequestHeaders();
	for (const auto& RequestHeader : Request->RequestHeaders)
	{
		ProcessingRequest->SetHeader(RequestHeader.Key, RequestHeader.Value);
	}

	// ダミーリクエスト設定
	IsDummyRequest = Request->IsDummyRequest;

	// リクエスト開始
	if (!IsDummyRequest)
	{
		ProcessingRequest->ProcessRequest();
	}
	bIsProcessingRequest = true;
	OnRequestStart.Broadcast(this, Request);
	OnRequestProgress.Broadcast(this, 0, 0);

	if (IsDummyRequest)
	{
		// TODO: シミュレートのために遅延実行したい
		FHttpResponsePtr HttpResponse = ProcessingRequest->GetResponse();
		OnRequestCompletedInternal(ProcessingRequest, HttpResponse, true);
	}

	return true;
}

void UWebApi::CancelRequest()
{
	FScopeLock ScopeLock(&SyncObject);

	if (!bIsProcessingRequest)
	{
		return;
	}

	ProcessingRequest->CancelRequest();
	bIsProcessingRequest = false;
}

bool UWebApi::IsProcessingRequest() const
{
	FScopeLock ScopeLock(&SyncObject);
	return bIsProcessingRequest;
}

void UWebApi::OnRequestProgressInternal(FHttpRequestPtr Request, int32 SentBytes, int32 ReceivedBytes)
{
	OnRequestProgress.Broadcast(this, SentBytes, ReceivedBytes);
}

void UWebApi::OnRequestCompletedInternal(FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool Success)
{
	FScopeLock ScopeLock(&SyncObject);

	// リクエスト完了
	bIsProcessingRequest = false;

	UWebApiResponseBody* Response = UWebApiResponseBody::Create(ResponseClass);
	if (!IsDummyRequest)
	{
		do {
			if (!InResponse.IsValid())
			{
				Response->ResponseCode = EHttpResponseCodes::Unknown;
				break;
			}

			if (!Success)
			{
				Response->ResponseCode = InResponse->GetResponseCode();
				break;
			}

			auto ResponseString = Cast<UWebApiResponseBodyString>(Response);
			if (ResponseString)
			{
				ResponseString->ResponseCode = InResponse->GetResponseCode();
				ResponseString->ResponseContent = InResponse->GetContentAsString();
				break;
			}

			auto ResponseBinary = Cast<UWebApiResponseBodyBinary>(Response);
			if (ResponseBinary)
			{
				ResponseBinary->ResponseCode = InResponse->GetResponseCode();
				ResponseBinary->ResponseContent = InResponse->GetContent();
				break;
			}

			Response->ResponseCode = EHttpResponseCodes::Unknown;
			UE_LOG(LogNekoNekoOnline, Warning, TEXT("Response Class is only UWebApiResponseBodyString/UWebApiResponseBodyBinary."));
		} while (false);
	}
	else
	{
		Response->ResponseCode = EHttpResponseCodes::Ok;
	}

	// フィルタリング
	for (auto FilterObject : ProcessingResponseFilters)
	{
		if (auto ResponseFilter = Cast<IWebApiResponseFilterInterface>(FilterObject))
		{
			Response = ResponseFilter->ExecuteResponseFilter(Response);
		}
		else if (FilterObject->GetClass()->ImplementsInterface(UWebApiResponseFilterBlueprintInterface::StaticClass()))
		{
			Response = IWebApiResponseFilterBlueprintInterface::Execute_ExecuteResponseFilter(FilterObject, Response);
		}
	}

	if (Success && Response != nullptr && SuccessResponseCodes.Find(Response->ResponseCode) >= 0)
	{
		OnRequestSuccess.Broadcast(this, Response);
	}
	else
	{
		OnRequestFailure.Broadcast(this, Response);
	}

	OnRequestCompleted.Broadcast(this, Response);
}

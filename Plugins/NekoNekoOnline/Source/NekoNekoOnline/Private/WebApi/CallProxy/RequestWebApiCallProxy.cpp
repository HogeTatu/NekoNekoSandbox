#include "NekoNekoOnlinePrivatePCH.h"
#include "WebApi.h"
#include "Request/WebApiRequestBody.h"
#include "Response/WebApiResponseBody.h"
#include "RequestWebApiCallProxy.h"

URequestWebApiCallbackParam::URequestWebApiCallbackParam(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

URequestWebApiCallProxy::URequestWebApiCallProxy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, CallbackParam(nullptr)
	, WebApi(nullptr)
	, Request(nullptr)
{
}

void URequestWebApiCallProxy::PostInitProperties()
{
	Super::PostInitProperties();

	// if (!HasAnyFlags(RF_ClassDefaultObject))
	// {
	// 	CallbackParam = NewObject<URequestWebApiCallbackParam>(GetTransientPackage());
	// }
}

URequestWebApiCallProxy* URequestWebApiCallProxy::RequestWebApi(UWebApi* WebApi, UWebApiRequestBody* Request, const TArray<UObject*>& RequestFilters, const TArray<UObject*>& ResponseFilters)
{
	URequestWebApiCallProxy* Proxy = NewObject<URequestWebApiCallProxy>();
	Proxy->WebApi = WebApi;
	Proxy->Request = Request;
	Proxy->RequestFilters = RequestFilters;
	Proxy->ResponseFilters = ResponseFilters;

	Proxy->CallbackParam = NewObject<URequestWebApiCallbackParam>();

	return Proxy;
}

void URequestWebApiCallProxy::Activate()
{
	if (!WebApi)
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("Requested WebApi is null."));
		OnRequestFailureInternal(WebApi, nullptr);
		return;
	}
	if (!Request)
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("Requested Request is null."));
		OnRequestFailureInternal(WebApi, nullptr);
		return;
	}

	// WebApi->OnRequestStart.AddUObject(this, &URequestWebApiCallProxy::OnRequestStartInternal);
	BindCallback(WebApi->OnRequestStart, "OnRequestStartInternal");
	BindCallback(WebApi->OnRequestProgress, "OnRequestProgressInternal");
	BindCallback(WebApi->OnRequestSuccess, "OnRequestSuccessInternal");
	BindCallback(WebApi->OnRequestFailure, "OnRequestFailureInternal");
	BindCallback(WebApi->OnRequestCompleted, "OnRequestCompletedInternal");

	WebApi->ProcessRequest(Request, RequestFilters, ResponseFilters);
}

void URequestWebApiCallProxy::OnRequestStartInternal(UWebApi* Api, UWebApiRequestBody* InRequest)
{
	CallbackParam->StartParam = FRequestWebApiStartParam(InRequest);
	OnStart.Broadcast(WebApi, CallbackParam);
}

void URequestWebApiCallProxy::OnRequestProgressInternal(UWebApi* Api, int32 SentBytes, int32 ReceivedBytes)
{
	CallbackParam->ProgressParam = FRequestWebApiProgressParam(SentBytes, ReceivedBytes);
	OnProgress.Broadcast(WebApi, CallbackParam);
}

void URequestWebApiCallProxy::OnRequestSuccessInternal(UWebApi* Api, UWebApiResponseBody* Response)
{
	CallbackParam->ResultParam = FRequestWebApiResultParam(Response);
	OnSuccess.Broadcast(WebApi, CallbackParam);
}

void URequestWebApiCallProxy::OnRequestFailureInternal(UWebApi* Api, UWebApiResponseBody* Response)
{
	CallbackParam->ResultParam = FRequestWebApiResultParam(Response);
	OnFailure.Broadcast(WebApi, CallbackParam);
}

void URequestWebApiCallProxy::OnRequestCompletedInternal(UWebApi* Api, UWebApiResponseBody* Response)
{
	CallbackParam->ResultParam = FRequestWebApiResultParam(Response);
	OnCompleted.Broadcast(WebApi, CallbackParam);
}


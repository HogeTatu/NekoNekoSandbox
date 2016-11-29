#include "NekoNekoOnlinePrivatePCH.h"
#include "Request/WebApiRequestBodyJson.h"
#include "Response/WebApiResponseBodyJson.h"
#include "PropertyFunctionLibrary.h"
#include "WebApiConvToJsonFilter.h"

UWebApiConvToJsonFilter* UWebApiConvToJsonFilter::GetConvToJsonFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiConvToJsonFilter>();
}

UWebApiRequestBody* UWebApiConvToJsonFilter::ExecuteRequestFilter(UWebApiRequestBody* Request)
{
	auto RequestUrlParam = Cast<UWebApiRequestBodyUrlParam>(Request);
	if (!RequestUrlParam)
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("Request is not UWebApiRequestBodyUrlParam"));
		return Request;
	}

	auto RequestJson = UWebApiRequestBody::Create<UWebApiRequestBodyJson>();

	// プロパティコピー
	auto PropertyNames = UWebApiResponseBody::GetPropertyNames(UWebApiRequestBodyUrlParam::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(RequestUrlParam, RequestJson, PropertyNames);

	return RequestJson;
}

UWebApiResponseBody* UWebApiConvToJsonFilter::ExecuteResponseFilter(UWebApiResponseBody* Response)
{
	auto ResponseString = Cast<UWebApiResponseBodyString>(Response);
	if (!ResponseString)
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("Response is not UWebApiResponseBodyString"));
		return Response;
	}

	auto ResponseJson = UWebApiResponseBody::Create<UWebApiResponseBodyJson>();

	// プロパティコピー
	auto PropertyNames = UWebApiResponseBody::GetPropertyNames(UWebApiResponseBodyString::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(ResponseString, ResponseJson, PropertyNames);

	return ResponseJson;
}

#include "NekoNekoOnlinePrivatePCH.h"
#include "Request/WebApiRequestBodyOAuth.h"
#include "PropertyFunctionLibrary.h"
#include "WebApiConvToOAuthFilter.h"

UWebApiConvToOAuthFilter* UWebApiConvToOAuthFilter::GetConvToOAuthFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiConvToOAuthFilter>();
}

UWebApiRequestBody* UWebApiConvToOAuthFilter::ExecuteRequestFilter(UWebApiRequestBody* Request)
{
	auto RequestUrlParam = Cast<UWebApiRequestBodyUrlParam>(Request);
	if (!RequestUrlParam)
	{
		UE_LOG(LogNekoNekoOnline, Warning, TEXT("Request is not UWebApiRequestBodyUrlParam"));
		return Request;
	}

	auto RequestOAuth = UWebApiRequestBody::Create<UWebApiRequestBodyOAuth>();

	// プロパティコピー
	auto PropertyNames = UWebApiResponseBody::GetPropertyNames(UWebApiRequestBodyUrlParam::StaticClass());
	UPropertyFunctionLibrary::CopyObjectProperties(RequestUrlParam, RequestOAuth, PropertyNames);

	return RequestOAuth;
}

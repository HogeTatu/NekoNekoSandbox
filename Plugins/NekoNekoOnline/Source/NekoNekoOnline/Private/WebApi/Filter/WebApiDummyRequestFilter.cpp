#include "NekoNekoOnlinePrivatePCH.h"
#include "WebApiDummyRequestFilter.h"

UWebApiDummyRequestFilter* UWebApiDummyRequestFilter::GetDummyRequestFilter()
{
	return StaticClass()->GetDefaultObject<UWebApiDummyRequestFilter>();
}

UWebApiRequestBody* UWebApiDummyRequestFilter::ExecuteRequestFilter(UWebApiRequestBody* Request)
{
	Request->IsDummyRequest = true;
	return Request;
}

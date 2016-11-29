#include "NekoNekoOnlinePrivatePCH.h"
#include "WebApiRequestBody.h"

TArray<FString> UWebApiRequestBody::CachedUObjectPropertyNames;

UWebApiRequestBody::UWebApiRequestBody(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, RequestHeaders()
	, IsDummyRequest(false)
{
}

UWebApiRequestBody* UWebApiRequestBody::Create(TSubclassOf<UWebApiRequestBody> RequestClass)
{
	return NewObject<UWebApiRequestBody>(GetTransientPackage(), RequestClass);
}

TArray<FString> UWebApiRequestBody::GetPropertyNames(TSubclassOf<UWebApiRequestBody> RequestClass)
{
	if (CachedUObjectPropertyNames.Num() <= 0)
	{
		for (auto Property : TFieldRange<const UProperty>(UObject::StaticClass()))
		{
			CachedUObjectPropertyNames.Add(Property->GetNameCPP());
		}
	}

	TArray<FString> PropertyNames;
	for (auto Property : TFieldRange<const UProperty>(RequestClass))
	{
		int32 Index = CachedUObjectPropertyNames.Find(Property->GetNameCPP());
		if (Index != INDEX_NONE)
		{
			PropertyNames.Add(Property->GetNameCPP());
		}
	}
	return PropertyNames;
}

void UWebApiRequestBody::SetRequestHeader(const FString& Key, const FString& Value)
{
	RequestHeaders.Add(Key, Value);
}

const FString& UWebApiRequestBody::GetRequestHeader(const FString& Key) const
{
	return RequestHeaders[Key];
}

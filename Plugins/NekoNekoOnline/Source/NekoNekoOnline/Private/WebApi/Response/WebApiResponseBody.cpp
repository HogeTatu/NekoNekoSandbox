#include "NekoNekoOnlinePrivatePCH.h"
#include "WebApiResponseBody.h"

TArray<FString> UWebApiResponseBody::CachedUObjectPropertyNames;

UWebApiResponseBody::UWebApiResponseBody(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, ResponseCode(0)
{
}

UWebApiResponseBody* UWebApiResponseBody::Create(TSubclassOf<UWebApiResponseBody> ResponseClass)
{
	return NewObject<UWebApiResponseBody>(GetTransientPackage(), ResponseClass);
}

TArray<FString> UWebApiResponseBody::GetPropertyNames(TSubclassOf<UWebApiResponseBody> ResponseClass)
{
	if (CachedUObjectPropertyNames.Num() <= 0)
	{
		for (auto Property : TFieldRange<const UProperty>(UObject::StaticClass()))
		{
			CachedUObjectPropertyNames.Add(Property->GetNameCPP());
		}
	}

	TArray<FString> PropertyNames;
	for (auto Property : TFieldRange<const UProperty>(ResponseClass))
	{
		int32 Index = CachedUObjectPropertyNames.Find(Property->GetNameCPP());
		if (Index != INDEX_NONE)
		{
			PropertyNames.Add(Property->GetNameCPP());
		}
	}
	return PropertyNames;
}

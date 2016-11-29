#include "NekoNekoOnlinePrivatePCH.h"
#include "JsonFunctionLibrary.h"
#include "Json.h"
#include "WebApiResponseBodyJson.h"

UWebApiResponseBodyJson::UWebApiResponseBodyJson(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UWebApiResponseBodyJson::GetJsonAccessor(FJsonAccessor& JsonAccessor)
{
	TSharedPtr<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(ResponseContent);

	TSharedPtr<FJsonObject> JsonObject;
	if(FJsonSerializer::Deserialize(JsonReader.ToSharedRef(), JsonObject) == false)
	{
		UE_LOG(LogNekoNekoOnline, Error, TEXT("FJsonSerializer::Deserialize failed. %s"), *ResponseContent);
		return false;
	}

	JsonAccessor = FJsonAccessor();
	{
		JsonAccessor.FieldName = TEXT("Root");
		JsonAccessor.JsonObject = JsonObject;
	}

	return true;
}

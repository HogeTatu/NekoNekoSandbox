#pragma once

#include "WebApiResponseBodyString.h"
#include "JsonAccessor.h"
#include "WebApiResponseBodyJson.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiResponseBodyJson : public UWebApiResponseBodyString
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * JSONアクセッサンを取得
	 * @param JsonAccessor JSONアクセッサ
	 * @return 成功時にtrue
	 */
	bool GetJsonAccessor(FJsonAccessor& JsonAccessor);

	/**
	 * JSONアクセッサンを取得
	 * @param JsonAccessor JSONアクセッサ
	 * @param Success 成功時にtrue
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void GetJsonAccessor(FJsonAccessor& JsonAccessor, bool& Success)
	{
		Success = GetJsonAccessor(JsonAccessor);
	}
};

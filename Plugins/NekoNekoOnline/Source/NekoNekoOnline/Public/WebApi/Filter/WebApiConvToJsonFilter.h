#pragma once

#include "WebApiRequestFilterInterface.h"
#include "WebApiResponseFilterInterface.h"
#include "WebApiConvToJsonFilter.generated.h"

/** JSON変換フィルター */
UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiConvToJsonFilter
	: public UObject
	, public IWebApiRequestFilterInterface
	, public IWebApiResponseFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * JSON変換フィルターを取得
	 * @return JSON変換フィルター
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	static UWebApiConvToJsonFilter* GetConvToJsonFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter(class UWebApiRequestBody* Request) override;

	// UWebApiResponseFilterInterface interface
	virtual class UWebApiResponseBody* ExecuteResponseFilter(class UWebApiResponseBody* Response) override;
};

#pragma once

#include "WebApiRequestFilterInterface.h"
#include "WebApiConvToOAuthFilter.generated.h"

/** OAuth変換フィルター */
UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiConvToOAuthFilter
	: public UObject
	, public IWebApiRequestFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * OAuth変換フィルターを取得
	 * @return OAuth変換フィルター
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	static UWebApiConvToOAuthFilter* GetConvToOAuthFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter(class UWebApiRequestBody* Request) override;
};

#pragma once

#include "WebApiRequestFilterInterface.h"
#include "WebApiDummyRequestFilter.generated.h"

/** ダミーリクエストフィルター */
UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiDummyRequestFilter
	: public UObject
	, public IWebApiRequestFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * ダミーリクエストフィルターを取得
	 * @return ダミーリクエストフィルター
	 */
	UFUNCTION(BlueprintPure, Category="NekoNeko|Online|WebApi")
	static UWebApiDummyRequestFilter* GetDummyRequestFilter();

	// UWebApiRequestFilterInterface interface
	virtual class UWebApiRequestBody* ExecuteRequestFilter(class UWebApiRequestBody* Request) override;
};

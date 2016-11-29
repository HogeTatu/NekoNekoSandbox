#pragma once

#include "WebApiResponseFilterBlueprintInterface.generated.h"

/** レスポンス時フィルターインターフェース */
UINTERFACE()
class NEKONEKOONLINE_API UWebApiResponseFilterBlueprintInterface : public UInterface
{
	GENERATED_BODY()
};

/** レスポンス時フィルターインターフェース */
class NEKONEKOONLINE_API IWebApiResponseFilterBlueprintInterface
{
	GENERATED_BODY()

public:
	/**
	 * レスポンス時フィルタリング実行
	 * @param Response レスポンス
	 * @return フィルタリング実行後レスポンス
	 */
	UFUNCTION(BlueprintNativeEvent, Category="NekoNeko|Online|WebApi")
	class UWebApiResponseBody* ExecuteResponseFilter(class UWebApiResponseBody* Response);
};

#pragma once

#include "WebApiRequestFilterBlueprintInterface.generated.h"

/** リクエスト時フィルターインターフェース */
UINTERFACE()
class NEKONEKOONLINE_API UWebApiRequestFilterBlueprintInterface : public UInterface
{
	GENERATED_BODY()
};

/** リクエスト時フィルターインターフェース */
class NEKONEKOONLINE_API IWebApiRequestFilterBlueprintInterface
{
	GENERATED_BODY()

public:
	/**
	 * リクエスト時フィルタリング実行
	 * @param Request リクエスト
	 * @return フィルタリング実行後リクエスト
	 */
	UFUNCTION(BlueprintNativeEvent, Category="NekoNeko|Online|WebApi")
	class UWebApiRequestBody* ExecuteRequestFilter(class UWebApiRequestBody* Request);
};

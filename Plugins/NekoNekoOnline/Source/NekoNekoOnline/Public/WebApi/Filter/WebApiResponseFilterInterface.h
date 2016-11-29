#pragma once

#include "WebApiResponseFilterInterface.generated.h"

/** レスポンス時フィルターインターフェース */
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class NEKONEKOONLINE_API UWebApiResponseFilterInterface : public UInterface
{
	GENERATED_BODY()
};

/** レスポンス時フィルターインターフェース */
class NEKONEKOONLINE_API IWebApiResponseFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * レスポンス時フィルタリング実行
	 * @param Response レスポンス
	 * @return フィルタリング実行後レスポンス
	 */
	virtual class UWebApiResponseBody* ExecuteResponseFilter(class UWebApiResponseBody* Response) = 0;
};

#pragma once

#include "WebApiRequestFilterInterface.generated.h"

/** リクエスト時フィルターインターフェース */
UINTERFACE(meta=(CannotImplementInterfaceInBlueprint))
class NEKONEKOONLINE_API UWebApiRequestFilterInterface : public UInterface
{
	GENERATED_BODY()
};

/** リクエスト時フィルターインターフェース */
class NEKONEKOONLINE_API IWebApiRequestFilterInterface
{
	GENERATED_BODY()

public:
	/**
	 * リクエスト時フィルタリング実行
	 * @param Request リクエスト
	 * @return フィルタリング実行後リクエスト
	 */
	virtual class UWebApiRequestBody* ExecuteRequestFilter(class UWebApiRequestBody* Request) = 0;
};

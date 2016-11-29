﻿#pragma once

#include "WebApiResponseBodyString.h"
#include "WebApiResponseBodyToken.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiResponseBodyToken : public UWebApiResponseBodyString
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * リクエストトークンを取得
	 * @param Token Token
	 * @param TokenSecret Token Secret
	 * @return 成功時にtrue
	 */
	bool GetRequestToken(FString& Token, FString& TokenSecret);

	/**
	 * リクエストトークンを取得
	 * @param Token Token
	 * @param TokenSecret Token Secret
	 * @param Success 成功時にtrue
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void GetRequestToken(FString& Token, FString& TokenSecret, bool Success)
	{
		Success = GetRequestToken(Token, TokenSecret);
	}
};

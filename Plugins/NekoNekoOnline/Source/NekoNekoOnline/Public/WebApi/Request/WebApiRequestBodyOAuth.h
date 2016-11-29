#pragma once

#include "WebApiRequestBodyPost.h"
#include "WebApiRequestBodyOAuth.generated.h"

/** OAuthパラメータ */
USTRUCT(BlueprintType)
struct NEKONEKOONLINE_API FOAuthParam
{
	GENERATED_BODY()

	/** URL */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	FString Url;

	/** Consumer Key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	FString ConsumerKey;

	/** Consumer Secret */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	FString ConsumerSecret;

	/** Token */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	FString Token;

	/** Token Secret */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	FString TokenSecret;

	/** PINコード */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|WebApi")
	FString Pin;
};

/** OAuthリクエスト */
UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiRequestBodyOAuth : public UWebApiRequestBodyPost
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * OAuthパラメータをリクエストヘッダーに設定
	 * @param Param OAuthパラメータ
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|WebApi")
	void SetAuthHeader(const FOAuthParam& Param);
};

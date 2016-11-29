#pragma once

#include "WebApiResponseBody.h"
#include "WebApiResponseBodyString.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiResponseBodyString : public UWebApiResponseBody
{
	GENERATED_UCLASS_BODY()

public:
	/** レスポンス文字列 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NekoNeko|Online|WebApi")
	FString ResponseContent;
};

#pragma once

#include "WebApiResponseBody.h"
#include "WebApiResponseBodyBinary.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiResponseBodyBinary : public UWebApiResponseBody
{
	GENERATED_UCLASS_BODY()

public:
	/** レスポンスバイナリ */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NekoNeko|Online|WebApi")
	TArray<uint8> ResponseContent;
};

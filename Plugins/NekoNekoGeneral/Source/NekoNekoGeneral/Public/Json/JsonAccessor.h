#pragma once

#include "JsonAccessor.generated.h"

/** JSONアクセッサ */
USTRUCT(BlueprintType)
struct NEKONEKOGENERAL_API FJsonAccessor
{
	GENERATED_USTRUCT_BODY()

	FJsonAccessor()
	{
	}

	FJsonAccessor(const FString& InFieldName, const TSharedPtr<FJsonObject>& InJsonObject)
		: FieldName(InFieldName)
		, JsonObject(InJsonObject)
	{
	}

	/** フィールド名 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Json")
	FString FieldName;

	/** JSONオブジェクト */
	TSharedPtr<FJsonObject> JsonObject;
};

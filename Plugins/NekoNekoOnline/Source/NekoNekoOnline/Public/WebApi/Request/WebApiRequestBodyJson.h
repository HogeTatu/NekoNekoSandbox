#pragma once

#include "WebApiRequestBodyUrlParam.h"
#include "WebApiRequestBodyJson.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiRequestBodyJson : public UWebApiRequestBodyUrlParam
{
	GENERATED_UCLASS_BODY()

public:
	// UWebApiRequestBody interface
	virtual EWebApiRequestType GetRequestType() const override { return EWebApiRequestType::Post; }
	virtual bool GetRequestBodyAsString(FString& RequestBody) const override;
	virtual void SetDefaultRequestHeaders() override;
};

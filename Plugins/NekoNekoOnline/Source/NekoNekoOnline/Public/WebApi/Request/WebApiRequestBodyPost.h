#pragma once

#include "WebApiRequestBodyUrlParam.h"
#include "WebApiRequestBodyPost.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UWebApiRequestBodyPost : public UWebApiRequestBodyUrlParam
{
	GENERATED_UCLASS_BODY()

public:
	// UWebApiRequestBody interface
	virtual EWebApiRequestType GetRequestType() const override { return EWebApiRequestType::Post; }
	virtual void SetDefaultRequestHeaders() override;
};

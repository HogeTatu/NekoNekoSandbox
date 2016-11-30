#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayDebuggerFunctionLibrary.generated.h"

/** GameplayDebugger関連ライブラリ */
UCLASS()
class NEKONEKOGENERAL_API UGameplayDebuggerFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * GameplayDebuggerの対象アクターを設定
	 * @param Actor GameplayDebuggerの対象アクター
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|General")
	static void SetGameplayDebugActor(AActor* Actor);
};

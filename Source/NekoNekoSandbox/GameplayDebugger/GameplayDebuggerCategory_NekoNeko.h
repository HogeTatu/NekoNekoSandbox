#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "GameplayDebuggerCategory.h"

class FGameplayDebuggerCategory_NekoNeko : public FGameplayDebuggerCategory
{
public:
	FGameplayDebuggerCategory_NekoNeko();

	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;

	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

protected:
	struct FRepData
	{
		FVector Location;
		FRotator Rotation;
		float Hate;

		void Serialize(FArchive& Ar);
	};
	FRepData DataPack;
};

#endif // WITH_GAMEPLAY_DEBUGGER

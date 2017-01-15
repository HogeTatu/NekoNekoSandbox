#include "NekoNekoGeneralPrivatePCH.h"
#include "GameplayDebuggerFunctionLibrary.h"

#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebuggerCategoryReplicator.h"
#endif

UGameplayDebuggerFunctionLibrary::UGameplayDebuggerFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UGameplayDebuggerFunctionLibrary::SetGameplayDebugActor(AActor* Actor)
{
#if WITH_GAMEPLAY_DEBUGGER
	if (!Actor)
	{
		UE_LOG(LogNekoNekoGeneral, Warning, TEXT("SetGameplayDebugActor failed."));
		return;
	}

	UWorld* World = Actor->GetWorld();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);

	for (TActorIterator<AGameplayDebuggerCategoryReplicator> It(World); It; ++It)
	{
		AGameplayDebuggerCategoryReplicator* Replicator = *It;
		if (Replicator && !Replicator->IsPendingKill())
		{
			if (PlayerController == Replicator->GetReplicationOwner())
			{
				Replicator->SetDebugActor(Actor);
			}
		}
	}
#endif
}

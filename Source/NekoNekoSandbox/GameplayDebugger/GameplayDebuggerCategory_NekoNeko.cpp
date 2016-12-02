#include "NekoNekoSandbox.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameplayDebuggerCategory_NekoNeko.h"

#if WITH_GAMEPLAY_DEBUGGER

FGameplayDebuggerCategory_NekoNeko::FGameplayDebuggerCategory_NekoNeko()
{
	SetDataPackReplication<FRepData>(&DataPack);
}

TSharedRef<FGameplayDebuggerCategory> FGameplayDebuggerCategory_NekoNeko::MakeInstance()
{
	return MakeShareable(new FGameplayDebuggerCategory_NekoNeko());
}

void FGameplayDebuggerCategory_NekoNeko::FRepData::Serialize(FArchive& Ar)
{
	Ar << Location << Rotation << Hate;
}

void FGameplayDebuggerCategory_NekoNeko::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	static const FName HatePropertyName(TEXT("Hate"));

	if (!DebugActor)
	{
		return;
	}

	for (auto Property : TFieldRange<const UProperty>(DebugActor->GetClass()))
	{
		if (Property->GetFName() == HatePropertyName)
		{
			auto FloatProperty = Cast<UFloatProperty>(Property);
			if (!FloatProperty)
			{
				continue;
			}

			// DataPackに対して必要なプロパティを設定
			DataPack.Location = DebugActor->GetActorLocation();
			DataPack.Rotation = DebugActor->GetActorRotation();
			DataPack.Hate = FloatProperty->GetPropertyValue(Property->ContainerPtrToValuePtr<float>(DebugActor));
		}
	}
}

void FGameplayDebuggerCategory_NekoNeko::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	FString HateString = FString::SanitizeFloat(DataPack.Hate);
	if (!HateString.IsEmpty())
	{
		// Hate値をスクリーンに表示
		CanvasContext.Printf(TEXT("Hate: {yellow}%s"), *HateString);

		// DebugActor上にHate値に合わせた色の箱を描画
		FLinearColor Color = UKismetMathLibrary::LinearColorLerpUsingHSV(
			FLinearColor::Green,
			FLinearColor::Red,
			FMath::Clamp(DataPack.Hate / 5.0f, 0.f, 1.f)
		);
		DrawDebugSolidBox(
			OwnerPC->GetWorld(),
			DataPack.Location + FVector(0, 0, 100),
			FVector(16, 16, 16),
			Color.Quantize()
		);
	}
}

#endif // WITH_GAMEPLAY_DEBUGGER

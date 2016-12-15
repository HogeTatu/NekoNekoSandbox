#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextureFunctionLibrary.generated.h"

/** テクスチャ関連ライブラリ */
UCLASS()
class NEKONEKOGENERAL_API UTextureFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * テクスチャデータ取得
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|General|Core")
	static bool GetTextureData(class UTexture2D* Texture, TArray<uint8>& Data, TEnumAsByte<EPixelFormat>& Format);
};

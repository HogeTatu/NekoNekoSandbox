#pragma once

#include "Components/ActorComponent.h"
#include "TextureBuildComponent.generated.h"

/** テクスチャ作成コンポーネント */
UCLASS(meta=(BlueprintSpawnableComponent), hideCategories=(Mobility))
class NEKONEKOGENERAL_API UTextureBuildComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	/**
	 * テクスチャ更新
	 * @param InTextureData テクスチャデータ
	 * @param InSizeX サイズX
	 * @param InSizeY サイズY
	 * @param InFormat ピクセルフォーマット
	 * @return 更新が完了したらtrue
	 */
	UFUNCTION(BlueprintCallable, Category="Texture")
	bool UpdateTexture(const TArray<uint8>& InTextureData, int32 InSizeX, int32 InSizeY, TEnumAsByte<EPixelFormat> InFormat);

	/**
	 * テクスチャ取得
	 * @return テクスチャ
	 */
	UFUNCTION(BlueprintPure, Category="Texture")
	UTexture2D* GetTexture() const;

private:
	/** テクスチャ */
	UPROPERTY()
	UTexture2D* Texture;
};

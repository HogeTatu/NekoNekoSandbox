﻿#include "NekoNekoGeneralPrivatePCH.h"
#include "TextureBuildComponent.h"

UTextureBuildComponent::UTextureBuildComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, MipIndexMax(0)
	, Texture(nullptr)
{
}

bool UTextureBuildComponent::UpdateTexture(const TArray<uint8>& InTextureData, int32 InSizeX, int32 InSizeY, TEnumAsByte<EPixelFormat> InFormat, int32 MipIndex)
{
	ETextureSourceFormat TextureFormat = TSF_Invalid;
	TextureCompressionSettings CompressionSettings = TC_Default;
	switch (InFormat)
	{
	case PF_B8G8R8A8:
		TextureFormat = TSF_BGRA8;
		break;
	case PF_FloatRGBA:
		TextureFormat = TSF_RGBA16F;
		CompressionSettings = TC_HDR;
		break;
	}

	// 必要ならテクスチャを作りなおす
	if (!Texture
		|| Texture->GetSizeX() != InSizeX
		|| Texture->GetSizeY() != InSizeY
		|| Texture->GetPixelFormat() != InFormat)
	{
		Texture = UTexture2D::CreateTransient(InSizeX, InSizeY, InFormat);

		Texture->PlatformData->Mips.Reset();
		for (int32 Index = 0; Index <= MipIndexMax; ++Index)
		{
			int32 SizeX = InSizeX >> Index;
			int32 SizeY = InSizeY >> Index;
			int32 NumBlocksX = SizeX / GPixelFormats[InFormat].BlockSizeX;
			int32 NumBlocksY = SizeY / GPixelFormats[InFormat].BlockSizeY;

			FTexture2DMipMap* Mip = new(Texture->PlatformData->Mips, Index) FTexture2DMipMap();
			Mip->SizeX = SizeX;
			Mip->SizeY = SizeY;
			Mip->BulkData.Lock(LOCK_READ_WRITE);
			Mip->BulkData.Realloc(NumBlocksX * NumBlocksY * GPixelFormats[InFormat].BlockBytes);
			Mip->BulkData.Unlock();
		}
	}

	if (Texture->PlatformData->Mips.Num() <= MipIndex)
	{
		return false;
	}

	FTexture2DMipMap& Mip = Texture->PlatformData->Mips[MipIndex];
	uint32* TextureData = (uint32*)Mip.BulkData.Lock(LOCK_READ_WRITE);
	const int32 TextureDataSize = Mip.BulkData.GetBulkDataSize();

	if (TextureDataSize != InTextureData.Num())
	{
		UE_LOG(LogTemp, Error, TEXT("TextureDataSize is invalid. TextureDataSize: %d, InTextureDataSize: %d"), TextureDataSize, InTextureData.Num());
		Mip.BulkData.Unlock();
		return false;
	}

	//　データコピー
	FMemory::Memcpy(TextureData, InTextureData.GetData(), TextureDataSize);

	Mip.BulkData.Unlock();
	Texture->UpdateResource();

	return true;
}

UTexture2D* UTextureBuildComponent::GetTexture() const
{
	return Texture;
}

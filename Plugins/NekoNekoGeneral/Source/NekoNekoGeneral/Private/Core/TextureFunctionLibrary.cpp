#include "NekoNekoGeneralPrivatePCH.h"
#include "TextureFunctionLibrary.h"

UTextureFunctionLibrary::UTextureFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UTextureFunctionLibrary::GetTextureData(UTexture2D* Texture, TArray<uint8>& Data, TEnumAsByte<EPixelFormat>& Format)
{
	if (!Texture)
	{
		return false;
	}

	FTexture2DMipMap& Mip = Texture->PlatformData->Mips[0];
	uint8* TextureData = (uint8*)Mip.BulkData.Lock(LOCK_READ_ONLY);
	const int32 DataSize = Mip.BulkData.GetBulkDataSize();

	Data.SetNum(DataSize);

	//　データコピー
	FMemory::Memcpy(Data.GetData(), TextureData, DataSize);

	Mip.BulkData.Unlock();

	Format = Texture->GetPixelFormat();

	return true;
}

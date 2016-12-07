#pragma once

#include "UdpPacket.h"
#include "UdpPacketSyncTexture.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UUdpPacketSyncTexture : public UUdpPacket
{
	GENERATED_BODY()

public:
	UUdpPacketSyncTexture(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, SizeX(0)
		, SizeY(0)
		, PixelFormat(EPixelFormat::PF_Unknown)
	{
	}

protected:
	/** パケットシリアライズ */
	virtual FArchive& SerializePacket(FArchive& Ar, UUdpPacket& Packet) override
	{
		UUdpPacketSyncTexture* PacketSyncTexture = Cast<UUdpPacketSyncTexture>(&Packet);
		if (!PacketSyncTexture)
		{
			UE_LOG(LogTemp, Error, TEXT("UUdpPacketSyncTexture Cast failed."));
			return Ar;
		}

		if (SizeX <= 0 || SizeY <= 0)
		{
			UE_LOG(LogTemp, Error, TEXT("Texture data is invalid."));
			return Ar;
		}

		Ar = Ar << SizeX << SizeY << PixelFormat;

		return Ar;
	}

public:
	/** 同期テクスチャサイズX */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	int32 SizeX;

	/** 同期テクスチャサイズY */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	int32 SizeY;

	/** 同期ピクセルフォーマット */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	TEnumAsByte<EPixelFormat> PixelFormat;
};

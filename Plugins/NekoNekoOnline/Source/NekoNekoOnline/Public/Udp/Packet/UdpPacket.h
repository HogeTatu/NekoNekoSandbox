#pragma once

#include "Networking.h"
#include "UdpPacket.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UUdpPacket : public UObject
{
	GENERATED_BODY()

public:
	UUdpPacket(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
	{
	}

	friend FArchive& operator<< (FArchive& Ar, UUdpPacket& Packet)
	{
		return Packet.SerializePacket(Ar, Packet);
	}

protected:
	/** パケットシリアライズ */
	virtual FArchive& SerializePacket(FArchive& Ar, UUdpPacket& Packet)
	{
		return Ar;
	}
};

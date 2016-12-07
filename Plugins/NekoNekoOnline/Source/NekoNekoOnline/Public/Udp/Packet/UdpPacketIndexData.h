#pragma once

#include "UdpPacket.h"
#include "UdpPacketIndexData.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UUdpPacketIndexData : public UUdpPacket
{
	GENERATED_BODY()

public:
	UUdpPacketIndexData(const FObjectInitializer& ObjectInitializer)
		: Super(ObjectInitializer)
		, Index(0)
	{
	}

	UFUNCTION(BlueprintPure, Category = "Udp|Packet")
	static int32 GetMultiIndexPacketSliceSize()
	{
		return 65000;
	}

	UFUNCTION(BlueprintCallable, Category = "Udp|Packet")
	static TArray<UUdpPacketIndexData*> CreateMultiIndexPacketData(UObject* Outer, const TArray<uint8> Data)
	{
		TArray<UUdpPacketIndexData*> Result;
		const int32 SliceSize = GetMultiIndexPacketSliceSize();
		int32 DataSize = Data.Num();
		int32 Index = 0;

		while (true)
		{
			int32 CopySize = FMath::Min(DataSize - (SliceSize * Index), SliceSize);

			TArray<uint8> SliceData;
			SliceData.Append((uint8*)(Data.GetData() + (SliceSize * Index)), CopySize);

			auto Packet = NewObject<UUdpPacketIndexData>(Outer);
			Packet->Index = Index;
			Packet->Data = SliceData;

			Result.Add(Packet);

			++Index;
			if (SliceSize * Index >= DataSize)
			{
				break;
			}
		}

		return Result;
	}

protected:
	/** パケットシリアライズ */
	virtual FArchive& SerializePacket(FArchive& Ar, UUdpPacket& Packet) override
	{
		UUdpPacketIndexData* PacketSyncIndexData = Cast<UUdpPacketIndexData>(&Packet);
		if (!PacketSyncIndexData)
		{
			UE_LOG(LogTemp, Error, TEXT("UUdpPacketIndexData Cast failed."));
			return Ar;
		}

		Ar = Ar << Index;
		Data.BulkSerialize(Ar);

		return Ar;
	}

public:
	/** 同期インデックス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	int32 Index;

	/** 同期データ */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	TArray<uint8> Data;
};

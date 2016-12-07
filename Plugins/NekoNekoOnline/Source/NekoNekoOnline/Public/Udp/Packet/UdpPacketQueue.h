#pragma once

#include "UdpPacket.h"
#include "Networking.h"
#include "Containers/Queue.h"
#include "UdpPacketQueue.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UUdpPacketQueue : public UObject
{
	GENERATED_BODY()

public:
	UUdpPacketQueue(const FObjectInitializer& ObjectInitializer);

public:
	/** パケットのクラス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	TSubclassOf<UUdpPacket> PacketClass;

public:
	/**
	 * パケット追加
	 */
	bool EnqueuePacket(const FArrayReaderPtr& Reader);

	/**
	 * パケット取り出し
	 */
	bool DequeuePacket(UUdpPacket*& Packet);

	/**
	 * パケット取り出し（BP用）
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|Udp", meta=(DisplayName="Dequeue Packet", DeterminesOutputType="InPacketClass", DynamicOutputParam="Packet"))
	bool DequeuePacketWithClass(TSubclassOf<UUdpPacket> InPacketClass, UUdpPacket*& Packet);

	/**
	 * スタックされたパケットを破棄
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|Udp")
	void ClearPackets();

private:
	/** パケットキュー */
	TQueue<UUdpPacket*> Packets;
};

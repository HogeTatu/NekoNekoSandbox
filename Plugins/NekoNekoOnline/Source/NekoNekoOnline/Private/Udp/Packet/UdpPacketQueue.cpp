#include "NekoNekoOnlinePrivatePCH.h"
#include "UdpPacketQueue.h"

UUdpPacketQueue::UUdpPacketQueue(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UUdpPacketQueue::EnqueuePacket(const FArrayReaderPtr& Reader)
{
	UUdpPacket* Packet = NewObject<UUdpPacket>(GetTransientPackage(), PacketClass);
	*Reader << *Packet;
	return Packets.Enqueue(Packet);
}

bool UUdpPacketQueue::DequeuePacket(UUdpPacket*& Packet)
{
	if (Packets.IsEmpty())
	{
		return false;
	}

	return Packets.Dequeue(Packet);
}

bool UUdpPacketQueue::DequeuePacketWithClass(TSubclassOf<UUdpPacket> InPacketClass, UUdpPacket*& Packet)
{
	return DequeuePacket(Packet);
}

void UUdpPacketQueue::ClearPackets()
{
	Packets.Empty();
}

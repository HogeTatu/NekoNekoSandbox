#include "NekoNekoOnlinePrivatePCH.h"
#include "Socket/UdpSocketReceiverExtend.h"
#include "Packet/UdpPacketQueue.h"
#include "UdpSocketReceiverComponent.h"

UUdpSocketReceiverComponent::UUdpSocketReceiverComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UUdpPacketQueue* UUdpSocketReceiverComponent::GetPacketQueue()
{
	UUdpSocketReceiverExtend* Receiver = Cast<UUdpSocketReceiverExtend>(Socket);
	if (!Receiver)
	{
		return nullptr;
	}

	return Receiver->GetPacketQueue();
}

TSubclassOf<UUdpSocketExtend> UUdpSocketReceiverComponent::GetSocketClass() const
{
	return UUdpSocketReceiverExtend::StaticClass();
}

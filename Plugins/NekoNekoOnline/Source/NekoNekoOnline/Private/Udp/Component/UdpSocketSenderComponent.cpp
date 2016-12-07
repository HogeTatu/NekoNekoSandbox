#include "NekoNekoOnlinePrivatePCH.h"
#include "Socket/UdpSocketSenderExtend.h"
#include "UdpSocketSenderComponent.h"

UUdpSocketSenderComponent::UUdpSocketSenderComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UUdpSocketSenderComponent::SendPacket(UUdpPacket* Packet)
{
	UUdpSocketSenderExtend* Sender = Cast<UUdpSocketSenderExtend>(Socket);
	if (!Sender)
	{
		return false;
	}

	return Sender->SendPacket(Packet);
}

TSubclassOf<UUdpSocketExtend> UUdpSocketSenderComponent::GetSocketClass() const
{
	return UUdpSocketSenderExtend::StaticClass();
}

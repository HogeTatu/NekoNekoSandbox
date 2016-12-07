#include "NekoNekoOnlinePrivatePCH.h"
#include "Packet/UdpPacket.h"
#include "UdpSocketSenderExtend.h"

static const int32 SEND_BUFFER_SIZE = 65507;

UUdpSocketSenderExtend::UUdpSocketSenderExtend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UUdpSocketSenderExtend::Initialize(const FString& InIp, int32 InPort, TSubclassOf<UUdpPacket> PacketClass)
{
	if (!Super::Initialize(InIp, InPort, PacketClass))
	{
		return false;
	}

	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool bIsValid;
	RemoteAddr->SetIp(*Ip, bIsValid);
	RemoteAddr->SetPort(Port);
	if (!bIsValid)
	{
		UE_LOG(LogTemp, Error, TEXT("Setup RemoteAddr failed."));

		Finalize();
		return false;
	}

	return true;
}

void UUdpSocketSenderExtend::Finalize()
{
	Super::Finalize();
}

bool UUdpSocketSenderExtend::SendPacket(UUdpPacket* Packet)
{
	if (!Socket.IsValid())
	{
		return false;
	}
	if (!Packet)
	{
		return false;
	}

	FArrayWriter Writer;
	int32 BytesSent = 0;
	Writer << *Packet;

	if (!Socket->SendTo(Writer.GetData(), Writer.Num(), BytesSent, *RemoteAddr))
	{
		UE_LOG(LogTemp, Error, TEXT("Packet send failed."));
		return false;
	}

	return true;
}

void UUdpSocketSenderExtend::SetupSocketBuilder(FUdpSocketBuilder& SocketBuilder)
{
	SocketBuilder = SocketBuilder.AsReusable()
		.WithBroadcast()
		.WithSendBufferSize(SEND_BUFFER_SIZE);
}

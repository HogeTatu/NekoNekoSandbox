#include "NekoNekoOnlinePrivatePCH.h"
#include "UdpSocketExtend.h"

UUdpSocketExtend::UUdpSocketExtend(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, Ip("127.0.0.1")
	, Port(50000)
{
}

bool UUdpSocketExtend::Initialize(const FString& InIp, int32 InPort, TSubclassOf<UUdpPacket> PacketClass)
{
	Ip = InIp;
	Port = InPort;
	FIPv4Address::Parse(Ip, IpAddress);

	// ソケット作成
	if (!CreateSocket())
	{
		Finalize();
		return false;
	}

	return true;
}

void UUdpSocketExtend::Finalize()
{
	// ソケット削除
	DeleteSocket();
}

bool UUdpSocketExtend::CreateSocket()
{
	auto SocketBuilder = FUdpSocketBuilder(TEXT("Socket"));
	SetupSocketBuilder(SocketBuilder);
	Socket = MakeShareable(SocketBuilder.Build());
	if (!Socket.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Build Socket failed."));
		return false;
	}

	return true;
}

void UUdpSocketExtend::DeleteSocket()
{
	if (!Socket.IsValid())
	{
		return;
	}

	Socket->Close();
}

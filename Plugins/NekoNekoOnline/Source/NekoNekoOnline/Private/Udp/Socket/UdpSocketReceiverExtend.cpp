#include "NekoNekoOnlinePrivatePCH.h"
#include "Packet/UdpPacketQueue.h"
#include "UdpSocketReceiverExtend.h"

static const int32 RECEIVE_BUFFER_SIZE = 65507;

UUdpSocketReceiverExtend::UUdpSocketReceiverExtend(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
, PacketQueue(nullptr)
{
}

bool UUdpSocketReceiverExtend::Initialize(const FString& InIp, int32 InPort, TSubclassOf<UUdpPacket> PacketClass)
{
	if (!Super::Initialize(InIp, InPort, PacketClass))
	{
		return false;
	}

	// 受信者作成
	if (!CreateReceiver())
	{
		Finalize();
		return false;
	}

	// パケットキュー作成
	PacketQueue = NewObject<UUdpPacketQueue>(GetTransientPackage(), UUdpPacketQueue::StaticClass());
	if (!PacketQueue)
	{
		UE_LOG(LogTemp, Error, TEXT("Create PacketQueue failed."));

		Finalize();
		return false;
	}
	PacketQueue->PacketClass = PacketClass;

	return true;
}

void UUdpSocketReceiverExtend::Finalize()
{
	// 受信者削除
	DeleteReceiver();

	Super::Finalize();
}

void UUdpSocketReceiverExtend::SetupSocketBuilder(FUdpSocketBuilder& SocketBuilder)
{
	if (IpAddress.IsMulticastAddress())
	{
		SocketBuilder = SocketBuilder.WithMulticastLoopback()
			.WithMulticastTtl(1)
			.JoinedToGroup(IpAddress);
	}
	else
	{
		SocketBuilder = SocketBuilder.BoundToAddress(IpAddress);
	}

	SocketBuilder = SocketBuilder.WithReceiveBufferSize(RECEIVE_BUFFER_SIZE)
		.BoundToPort(Port);
}

bool UUdpSocketReceiverExtend::CreateReceiver()
{
	Receiver = MakeShareable(new FUdpSocketReceiver(Socket.Get(), FTimespan::FromMilliseconds(1), TEXT("Receiver")));

	if (!Receiver.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Construct Receiver failed."));
		return false;
	}

	Receiver->OnDataReceived().BindUObject(this, &UUdpSocketReceiverExtend::OnDataReceived);
	Receiver->Start();

	return true;
}

void UUdpSocketReceiverExtend::DeleteReceiver()
{
	if (!Receiver.IsValid())
	{
		return;
	}

	Receiver->Stop();
}

void UUdpSocketReceiverExtend::OnDataReceived(const FArrayReaderPtr& Reader, const FIPv4Endpoint& Sender)
{
	// if (GEngine)
	// {
	// 	FString DataStr = FString::FromHexBlob(Reader->GetData(), Reader->Num());
	// 	UE_LOG(LogTemp, Log, TEXT("%s"), *DataStr);
	// }

	if (!PacketQueue)
	{
		return;
	}

	if (!PacketQueue->EnqueuePacket(Reader))
	{
		UE_LOG(LogTemp, Error, TEXT("EnqueuePacket failed."));
	}
}

#pragma once

#include "UdpSocketExtend.h"
#include "UdpSocketSenderExtend.generated.h"

UCLASS()
class NEKONEKOONLINE_API UUdpSocketSenderExtend : public UUdpSocketExtend
{
	GENERATED_BODY()

public:
	UUdpSocketSenderExtend(const FObjectInitializer& ObjectInitializer);

public:
	/**
	 * 初期化処理
	 */
	virtual bool Initialize(const FString& Ip, int32 Port, TSubclassOf<class UUdpPacket> PacketClass) override;

	/**
	 * 終了処理
	 */
	virtual void Finalize() override;

	/**
	 * パケット送信
	 */
	bool SendPacket(UUdpPacket* Packet);

protected:
	/**
	 * ソケットビルダーをセットアップ
	 */
	virtual void SetupSocketBuilder(FUdpSocketBuilder& SocketBuilder) override;

protected:
	TSharedPtr<FInternetAddr> RemoteAddr;
};

#pragma once

#include "UdpSocketExtend.h"
#include "UdpSocketReceiverExtend.generated.h"

UCLASS()
class NEKONEKOONLINE_API UUdpSocketReceiverExtend : public UUdpSocketExtend
{
	GENERATED_BODY()

public:
	UUdpSocketReceiverExtend(const FObjectInitializer& ObjectInitializer);

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
	 * パケットキュー取得
	 */
	class UUdpPacketQueue* GetPacketQueue()
	{
		return PacketQueue;
	}

protected:
	/**
	 * ソケットビルダーをセットアップ
	 */
	virtual void SetupSocketBuilder(FUdpSocketBuilder& SocketBuilder) override;

	/**
	 * 受信者を作成
	 */
	bool CreateReceiver();

	/**
	 * 受信者を削除
	 */
	void DeleteReceiver();

	/**
	 * データ受け取りコールバック
	 */
	void OnDataReceived(const FArrayReaderPtr& Reader, const FIPv4Endpoint& Sender);

protected:
	/** パケットキュー */
	UPROPERTY(Transient)
	class UUdpPacketQueue* PacketQueue;

	/** レシーバー */
	TSharedPtr<FUdpSocketReceiver> Receiver;
};

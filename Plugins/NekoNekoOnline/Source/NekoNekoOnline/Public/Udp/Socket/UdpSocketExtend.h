#pragma once

#include "Networking.h"
#include "UdpSocketExtend.generated.h"

UCLASS()
class NEKONEKOONLINE_API UUdpSocketExtend : public UObject
{
	GENERATED_BODY()

public:
	UUdpSocketExtend(const FObjectInitializer& ObjectInitializer);

public:
	/**
	 * 初期化処理
	 */
	virtual bool Initialize(const FString& Ip, int32 Port, TSubclassOf<class UUdpPacket> PacketClass);

	/**
	 * 終了処理
	 */
	virtual void Finalize();

protected:
	/**
	 * ソケットを作成
	 */
	bool CreateSocket();

	/**
	 * ソケットを削除
	 */
	void DeleteSocket();

	/**
	 * ソケットビルダーをセットアップ
	 */
	virtual void SetupSocketBuilder(FUdpSocketBuilder& SocketBuilder) {}

protected:
	/** IPアドレス文字列 */
	FString Ip;

	/** IPアドレス */
	FIPv4Address IpAddress;

	/** ポート番号 */
	int32 Port;

	/** ソケット */
	TSharedPtr<FSocket> Socket;
};

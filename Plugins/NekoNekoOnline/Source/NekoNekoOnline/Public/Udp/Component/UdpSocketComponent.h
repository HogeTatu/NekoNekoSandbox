#pragma once

#include "Socket/UdpSocketExtend.h"
#include "Packet/UdpPacket.h"
#include "UdpSocketComponent.generated.h"

UCLASS(BlueprintType, Blueprintable)
class NEKONEKOONLINE_API UUdpSocketComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUdpSocketComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** ソケットのクラスを取得 */
	virtual TSubclassOf<class UUdpSocketExtend> GetSocketClass() const
	{
		return UUdpSocketExtend::StaticClass();
	}

public:
	/** IPアドレス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	FString IpAddress;

	/** ポート */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	int32 Port;

	/** IP/Portを上書きするコンフィグファイル名 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	FString OverwriteConfigFileName;

	/** パケットのクラス */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="NekoNeko|Online|Udp")
	TSubclassOf<UUdpPacket> PacketClass;

	/** ソケット */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="NekoNeko|Online|Udp")
	class UUdpSocketExtend* Socket;
};

#pragma once

#include "UdpSocketComponent.h"
#include "UdpSocketReceiverComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class NEKONEKOONLINE_API UUdpSocketReceiverComponent : public UUdpSocketComponent
{
	GENERATED_BODY()

public:
	UUdpSocketReceiverComponent(const FObjectInitializer& ObjectInitializer);

public:
	/**
	 * パケットキュー取得
	 */
	UFUNCTION(BlueprintPure, Category = "NekoNeko|Online|Udp")
	class UUdpPacketQueue* GetPacketQueue();

protected:
	/** ソケットのクラスを取得 */
	virtual TSubclassOf<class UUdpSocketExtend> GetSocketClass() const override;
};

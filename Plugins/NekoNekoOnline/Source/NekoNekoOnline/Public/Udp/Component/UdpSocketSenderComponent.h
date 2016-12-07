#pragma once

#include "UdpSocketComponent.h"
#include "UdpSocketSenderComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class NEKONEKOONLINE_API UUdpSocketSenderComponent : public UUdpSocketComponent
{
	GENERATED_BODY()

public:
	UUdpSocketSenderComponent(const FObjectInitializer& ObjectInitializer);

public:
	/**
	 * パケット送信
	 */
	UFUNCTION(BlueprintCallable, Category="NekoNeko|Online|Udp")
	bool SendPacket(UUdpPacket* Packet);

protected:
	/** ソケットのクラスを取得 */
	virtual TSubclassOf<class UUdpSocketExtend> GetSocketClass() const override;
};

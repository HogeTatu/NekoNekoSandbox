#include "NekoNekoOnlinePrivatePCH.h"
#include "Socket/UdpSocketExtend.h"
#include "UdpSocketComponent.h"

UUdpSocketComponent::UUdpSocketComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, IpAddress("127.0.0.1")
	, Port(50000)
	, PacketClass(UUdpPacket::StaticClass())
	, Socket(nullptr)
{
}

void UUdpSocketComponent::BeginPlay()
{
	Super::BeginPlay();

	Socket = NewObject<UUdpSocketExtend>(GetTransientPackage(), GetSocketClass());
	if (!Socket)
	{
		UE_LOG(LogTemp, Error, TEXT("Create UUdpSocketExtend failed."));
		return;
	}

	// コンフィグファイルが存在すればIP/Portを上書き
	const FString ConfigFilePath = FPaths::GameConfigDir() + OverwriteConfigFileName;
	if (FPaths::FileExists(ConfigFilePath))
	{
		FString FileContents;
		if (FFileHelper::LoadFileToString(FileContents, *ConfigFilePath))
		{
			// 改行コード調整
			FileContents = FileContents.Replace(TEXT("\r"), TEXT(""));

			// ライン分割
			TArray<FString> FileContentStrings;
			FileContents.ParseIntoArray(FileContentStrings, TEXT("\n"), true);

			if (FileContentStrings.Num() < 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("SocketConfigFile '%s' is invalid format."), *ConfigFilePath);
			}
			else
			{
				// IP/Port上書き
				IpAddress = FileContentStrings[0];
				Port = FCString::Atoi(*FileContentStrings[1]);
			}
		}
	}

	if (!Socket->Initialize(IpAddress, Port, PacketClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Socket Initialize failed."));

		// 解放はGCまかせ
		Socket = nullptr;

		return;
	}
}

void UUdpSocketComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Socket)
	{
		Socket->Finalize();

		// 解放はGCまかせ
		// Socket = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

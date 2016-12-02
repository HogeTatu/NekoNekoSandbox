#include "NekoNekoSandbox.h"

#if WITH_GAMEPLAY_DEBUGGER
#include "GameplayDebugger.h"
#include "GameplayDebugger/GameplayDebuggerCategory_NekoNeko.h"
#endif // WITH_GAMEPLAY_DEBUGGER

class FNekoNekoSandboxModule : public FDefaultGameModuleImpl
{
	// Begin IModuleInterface
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_PRIMARY_GAME_MODULE( FNekoNekoSandboxModule, NekoNekoSandbox, "NekoNekoSandbox" );

void FNekoNekoSandboxModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();

#if WITH_GAMEPLAY_DEBUGGER
	IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
	GameplayDebuggerModule.RegisterCategory("NekoNeko", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGameplayDebuggerCategory_NekoNeko::MakeInstance));
	GameplayDebuggerModule.NotifyCategoriesChanged();
#endif
}

void FNekoNekoSandboxModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();

#if WITH_GAMEPLAY_DEBUGGER
	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
		GameplayDebuggerModule.UnregisterCategory("NekoNeko");
		GameplayDebuggerModule.NotifyCategoriesChanged();
	}
#endif
}

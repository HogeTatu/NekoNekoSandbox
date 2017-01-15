// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class NekoNekoSandbox : ModuleRules
{
	public NekoNekoSandbox(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);

		if (Target.Type != TargetRules.TargetType.Server)
		{
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"InputCore",
				}
			);
		}

		if (UEBuildConfiguration.bBuildDeveloperTools || (Target.Configuration != UnrealTargetConfiguration.Shipping && Target.Configuration != UnrealTargetConfiguration.Test))
		{
			PrivateDependencyModuleNames.Add("GameplayDebugger");
			Definitions.Add("WITH_GAMEPLAY_DEBUGGER=1");
		}
	}
}

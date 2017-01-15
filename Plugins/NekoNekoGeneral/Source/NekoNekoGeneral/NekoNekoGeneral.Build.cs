// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NekoNekoGeneral : ModuleRules
{
	public NekoNekoGeneral(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[]
			{
				"NekoNekoGeneral/Public",
				"NekoNekoGeneral/Public/Core",
				"NekoNekoGeneral/Public/Json",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
				"NekoNekoGeneral/Private",
				"NekoNekoGeneral/Private/Core",
				"NekoNekoGeneral/Private/Json",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Json",
				"RenderCore",
			}
		);

		if (Target.Type != TargetRules.TargetType.Server)
		{
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Slate",
					"SlateCore",
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

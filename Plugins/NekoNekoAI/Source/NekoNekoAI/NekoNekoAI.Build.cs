// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NekoNekoAI : ModuleRules
{
	public NekoNekoAI(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[] {
				"NekoNekoAI/Public"
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"NekoNekoAI/Private",
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
	}
}

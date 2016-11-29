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
				"Slate",
				"SlateCore",
				"Json",
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}

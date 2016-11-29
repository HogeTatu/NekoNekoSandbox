// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NekoNekoOnline : ModuleRules
{
	public NekoNekoOnline(TargetInfo Target)
	{
		PublicIncludePaths.AddRange(
			new string[]
			{
				"NekoNekoOnline/Public",
				"NekoNekoOnline/Public/WebApi",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
				"NekoNekoOnline/Private",
				"NekoNekoOnline/Private/WebApi",
				"NekoNekoOnline/Private/ThirdParty/liboauthcpp",
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
                "HTTP",
                "Json",
                "NekoNekoGeneral",
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}

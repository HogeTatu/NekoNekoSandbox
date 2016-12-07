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
				"NekoNekoOnline/Public/Encode",
				"NekoNekoOnline/Public/Udp",
				"NekoNekoOnline/Public/WebApi",
			}
		);

		PrivateIncludePaths.AddRange(
			new string[]
			{
				"NekoNekoOnline/Private",
				"NekoNekoOnline/Private/Encode",
				"NekoNekoOnline/Private/Udp",
				"NekoNekoOnline/Private/WebApi",
				"NekoNekoOnline/Private/ThirdParty/liboauthcpp",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "Networking",
                "Sockets",
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
                "Networking",
                "Sockets",
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

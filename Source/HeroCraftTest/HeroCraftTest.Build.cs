// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HeroCraftTest : ModuleRules
{
	public HeroCraftTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

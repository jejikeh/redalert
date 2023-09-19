// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ratdeath : ModuleRules
{
	public Ratdeath(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"HeadMountedDisplay", 
			"EnhancedInput",
			"InventorySystem"
		});
	}
}

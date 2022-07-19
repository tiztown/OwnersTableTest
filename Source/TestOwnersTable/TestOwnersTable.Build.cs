// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TestOwnersTable : ModuleRules
{
	public TestOwnersTable(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new string[] {"ImageCore"});
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG" });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"TestOwnersTable/Components"
		});
	}
}

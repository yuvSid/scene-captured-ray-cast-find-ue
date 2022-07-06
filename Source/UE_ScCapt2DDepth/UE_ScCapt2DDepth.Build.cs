// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_ScCapt2DDepth : ModuleRules
{
	public UE_ScCapt2DDepth(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Latest;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}

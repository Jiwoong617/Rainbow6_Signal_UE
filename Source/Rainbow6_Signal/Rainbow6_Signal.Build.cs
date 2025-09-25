// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Rainbow6_Signal : ModuleRules
{
	public Rainbow6_Signal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
			"Niagara",
			"NavigationSystem",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Rainbow6_Signal",
			"Rainbow6_Signal/Variant_Horror",
			"Rainbow6_Signal/Variant_Horror/UI",
			"Rainbow6_Signal/Variant_Shooter",
			"Rainbow6_Signal/Variant_Shooter/AI",
			"Rainbow6_Signal/Variant_Shooter/UI",
			"Rainbow6_Signal/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

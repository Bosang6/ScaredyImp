// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ScaredyImp : ModuleRules
{
	public ScaredyImp(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ScaredyImp",
			"ScaredyImp/Variant_Platforming",
			"ScaredyImp/Variant_Platforming/Animation",
			"ScaredyImp/Variant_Combat",
			"ScaredyImp/Variant_Combat/AI",
			"ScaredyImp/Variant_Combat/Animation",
			"ScaredyImp/Variant_Combat/Gameplay",
			"ScaredyImp/Variant_Combat/Interfaces",
			"ScaredyImp/Variant_Combat/UI",
			"ScaredyImp/Variant_SideScrolling",
			"ScaredyImp/Variant_SideScrolling/AI",
			"ScaredyImp/Variant_SideScrolling/Gameplay",
			"ScaredyImp/Variant_SideScrolling/Interfaces",
			"ScaredyImp/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}

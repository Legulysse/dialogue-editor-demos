// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DialogueDemoUnrealEditor : ModuleRules
{
	public DialogueDemoUnrealEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"InputCore",
			"HeadMountedDisplay",
			"DialogueDemoUnreal"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{            
			"Json",            
			"JsonUtilities"
		});

		/*PrivateIncludePathModuleNames.AddRange(
			new string[] {
				"AssetRegistry",
				"AssetTools",
				"MainFrame",
				"BlueprintGraph"
			}
		);*/
	}
}

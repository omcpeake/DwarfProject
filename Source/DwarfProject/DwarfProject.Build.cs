// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DwarfProject : ModuleRules
{
	public DwarfProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","GameplayTasks", "EnhancedInput", "AIModule", "UMG" });

        //idk if I need this but Im gonna leave it here
        //PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}

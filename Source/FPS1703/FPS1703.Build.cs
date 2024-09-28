using System.IO;
using UnrealBuildTool;

public class FPS1703 : ModuleRules
{
	public FPS1703(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "GameplayTasks", "NavigationSystem" });

        PublicIncludePaths.AddRange(new string[] { "FPS1703/Pickup", "FPS1703/WeaponComponents", 
												   "FPS1703/AI", "FPS1703/AI/Tasks", "FPS1703/AI/Services", 
											       "FPS1703/UI", "FPS1703/Menu", "FPS1703/Menu/UI", "FPS1703/Constructors" });
    }

}

using UnrealBuildTool;

public class ProjectAfterlight : ModuleRules
{
	public ProjectAfterlight(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"AIModule",
			"NavigationSystem",
			"GameplayTasks",
			"UMG",
			"ChaosVehicles",
			"Niagara",
			"GameplayAbilities",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}

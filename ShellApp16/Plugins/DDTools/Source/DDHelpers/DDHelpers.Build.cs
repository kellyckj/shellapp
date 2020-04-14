//
// DDHelpers.Build.cs
//
//  Generated on January 27 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2019 Regents of the University of California
//

using UnrealBuildTool;

public class DDHelpers : ModuleRules
{
	public DDHelpers(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
			}
			);


		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);


		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"UMG"
			}
			);


		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
                "InputCore",
				"Slate",
				"SlateCore",
                "DDLog"
			}
			);
            
        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd"
            }
            );
        }


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}

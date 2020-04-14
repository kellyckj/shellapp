//
// DDHelpers.Build.cs
//
//  Generated on January 27 2020
//  Template created by Peter Gusev on 27 January 2020.
//  Copyright 2013-2019 Regents of the University of California
//

using UnrealBuildTool;

public class DDManager : ModuleRules
{
	public DDManager(ReadOnlyTargetRules Target) : base(Target)
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
				"UMG",
				"DDHelpers"
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


		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);
	}
}

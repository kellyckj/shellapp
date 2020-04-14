// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GrasshopperAREditorTarget : TargetRules
{
	public GrasshopperAREditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GrasshopperAR", "DDLog" } );
	}
}

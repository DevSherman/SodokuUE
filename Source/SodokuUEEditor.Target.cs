using UnrealBuildTool;
using System.Collections.Generic;

public class SodokuUEEditorTarget : TargetRules
{
	public SodokuUEEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "SodokuUE" } );
	}
}

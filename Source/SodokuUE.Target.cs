using UnrealBuildTool;
using System.Collections.Generic;

public class SodokuUETarget : TargetRules
{
	public SodokuUETarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "SodokuUE" } );
	}
}

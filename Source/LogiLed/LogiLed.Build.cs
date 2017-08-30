// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;

namespace UnrealBuildTool.Rules
{
	using System.IO;

	public class LogiLed : ModuleRules
	{
		public LogiLed(ReadOnlyTargetRules Target) : base(Target)
		{
			PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Engine",
				});

			PrivateIncludePaths.AddRange(
				new string[] {
					"LogiLed/Private",
					"LogiLed/Private/Assets",
				});

			if (Target.bBuildEditor)
			{
				PrivateDependencyModuleNames.Add("UnrealEd");
			}

			// add Logitech SDK libraries
			string LogiDir = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty"));
			string LibDir = Path.Combine(LogiDir, "lib");

			PrivateIncludePaths.Add(Path.Combine(LogiDir, "include"));

			if (Target.Platform == UnrealTargetPlatform.Win32)
			{
				PublicLibraryPaths.Add(Path.Combine(LibDir, "x86"));
				PublicAdditionalLibraries.Add("LogitechLEDLib.lib");
			}
			else if (Target.Platform == UnrealTargetPlatform.Win64)
			{
				PublicLibraryPaths.Add(Path.Combine(LibDir, "x64"));
				PublicAdditionalLibraries.Add("LogitechLEDLib.lib");
			}
			else
			{
				System.Console.WriteLine("Logitech SDK does not support this platform");
			}
		}
	}
}
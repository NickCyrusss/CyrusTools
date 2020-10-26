// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class CyrusTools : ModuleRules
{
	private string ModulePath
	{
		get { return ModuleDirectory; }
	}

	private string ThirdPartyPath
	{
		get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
	}
	public CyrusTools(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
                //"Public",
                Path.Combine(ThirdPartyPath, "assimp/include"),
				// ... add public include paths required here ...
			}
            );
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"RuntimeMeshComponent",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "UMG",
                "Projects",
                "DesktopPlatform",
                // ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
		
		if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
		{
			string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "Win64" : "Win32";
			PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "assimp/lib",PlatformString, "assimp-vc141-mt.lib"));
			//RuntimeDependencies.Add(Path.Combine(ThirdPartyPath, "assimp/bin/",PlatformString, "assimp-vc141-mt.dll"));
		}
		// else if(Target.Platform == UnrealTargetPlatform.Mac)
		// {
		// 	string PlatformString =  "Mac";
		// 	PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "assimp/lib/",PlatformString, "/libassimp.4.1.0.dylib"));
		// }
	}
}

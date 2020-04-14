# GrasshopperAR
UE4 Shell App for Grasshopper AR project.

## Description

The app supports AR-capable devices and desktop devices, compiled from the same source code base.
Depending on the platform, different classes are loaded:
* AR platforms:
	* *AR Pawn*
	* *AR Player Controller* 
* desktop platforms:
	* *VR Pawn* (/Spectator Pawn/)
	* *VR Player Controller*

There are also different levels for AR/VR.

> ❗️This workflow is being [tested](https://udn.unrealengine.com/questions/553302/how-to-load-different-gamemodes-for-different-plat.html). Need to confirm if it works and whether it’ll play nicely with the multiplayer.

## Project folder structure

```
.
├── Config    // configuration files for multiplatform build
├── Content   // ShellApp content goes here
│   ├── Blueprints
│   │   ├── BP_ARController.uasset   // AR Player Controller
│   │   ├── BP_ARGameMode.uasset     // AR Game Mode
│   │   ├── BP_ARPawn.uasset         // AR Pawn
│   │   ├── BP_VRController.uasset   // VR Player Controller
│   │   ├── BP_VRGameMode.uasset     // VR Game Mode
│   │   ├── BP_VRPawn.uasset         // VR Pawn
│   │   └── UI
│   │       ├── BP_DebugMenu.uasset
│   │       ├── WD_PluginButton.uasset
│   │       └── BP_Master.uasset     // Master UI
│   ├── Data
│   │   └── D_SessionConfig.uasset   // AR Session Config file
│   └── Maps
│       ├── M_ARLevel0.umap   // AR Level Map
│       └── M_VRLevel0.umap   // VR Level Map
├── Plugins
│   ├── ...       // ALL DEV GROUPS PLUGINS ARE HERE
│   └── DDTools   // DDTools plugin (development tools)
├── Source        // ShellApp source code. SHOULD NOT BE TOUCHED
│   ├── GrasshopperAR
│   │   ├── GrasshopperAR.Build.cs
│   │   ├── GrasshopperAR.cpp
│   │   ├── GrasshopperAR.h
│   │   ├── GrasshopperARGameModeBase.cpp
│   │   └── GrasshopperARGameModeBase.h
│   ├── GrasshopperAR.Target.cs
│   └── GrasshopperAREditor.Target.cs
└── GrasshopperAR.uproject
```

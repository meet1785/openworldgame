# Project Afterlight - Automated Deployment & Packaging

## Overview
This document outlines the final steps to compile, package, and prepare the game for publishing on Steam/Epic Games. Since the C++ architecture is completely written, you must now execute the engine build process.

## 1. Engine Compilation
1. Ensure Unreal Engine 5.3+ is installed.
2. Right-click `ProjectAfterlight.uproject` -> **Generate Visual Studio project files**.
3. Open `ProjectAfterlight.sln` in Visual Studio 2022.
4. Set build configuration to `Development Editor` and compile.
5. Open the project in Unreal Editor.

## 2. Asset Generation (Automated)
Run the provided python script inside the Unreal Engine Output Log (requires Python Editor Script Plugin to be enabled):
`py "C:/path/to/Tools/GeneratePlaceholderAssets.py"`
This will build the required directory structure and placeholder materials for the factions.

## 3. Data Setup
1. Create Data Tables inheriting from `FALDialogueLine` and `FALItemData`.
2. Populate the Item database.
3. Assign the `ALPlayerCharacter` to a Blueprint and set it as the Default Pawn in `AfterlightGameMode`.

## 4. Packaging the Game
1. Go to **Platforms -> Windows -> Package Project**.
2. Select an output directory.
3. Ensure the Build Configuration is set to **Shipping**.
4. The packaging process will cook all maps, strip out debug symbols, and generate the final `.exe`.

## 5. Store Readiness Metadata
*   **App Name:** Project: Afterlight
*   **Genre:** Action-Adventure, Open World
*   **Features:** Single-player, Full Controller Support, Steam Cloud Saves (mapped to the UE5 SaveSystem directory).
*   **Target Specs:** 
    *   *Min:* Quad-core CPU, 8GB RAM, GTX 1060 / RX 580 (1080p 30fps, TSR Performance)
    *   *Rec:* Octa-core CPU, 16GB RAM, RTX 3060 / RX 6700XT (1440p 60fps, TSR Quality)

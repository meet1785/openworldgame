# PROJECT: AFTERLIGHT - Technical Architecture

## 1. Engine & Platform
**Engine:** Unreal Engine 5.3+
**Language:** C++ (Core Systems, Performance-critical logic) & Blueprints (UI, Config, Level Scripting).
**Target Platform:** Windows PC (DX12). Architected for future console porting (PS5/Xbox Series).

## 2. Core Architecture Philosophy
The game uses a highly modular, data-driven architecture based on UE5's Gameplay Ability System (GAS) for combat and progression, and Subsystems for global management.

### Key Modules:
*   **Core:** `GameMode`, `GameInstance`, `PlayerController`, `CheatManager`.
*   **Characters:** `BaseCharacter`, `PlayerCharacter`, `EnemyCharacter`, `NPCCharacter`.
*   **Combat:** Weapon inventory, Ballistics, Damage calculation, Gameplay Ability System (GAS).
*   **AI:** Behavior Trees, Environment Query System (EQS), StateTree for crowd/traffic.
*   **Vehicles:** Chaos Vehicles system integration, Vehicle possession, Traffic splines.
*   **World:** Time of Day manager, Weather subsystem, World Partition configuration.
*   **Systems:** Save/Load subsystem, Quest/Mission Manager, Wanted/Pursuit system.

## 3. World Streaming & Optimization
*   **World Partition:** Used for the entire open world map. Grid size tailored to vehicle speed.
*   **Data Layers:** Used to swap out geometry for story states (e.g., destroyed buildings) without duplicating the map.
*   **HLODs (Hierarchical Level of Detail):** Generated for distant cityscapes.
*   **Nanite & Lumen:** Enabled for all static meshes and global illumination to handle the dense urban environment dynamically.
*   **Object Pooling:** Used for projectiles, traffic vehicles, and pedestrian NPCs to prevent hitching during instantiation.

## 4. Data-Driven Design
All easily tunable values are exposed via Data Assets (`UDataAsset`) or Data Tables (`UDataTable`).
*   `WeaponStatsDA`: Recoil, damage, fire rate, magazine size.
*   `VehicleHandlingDA`: Torque, steering curves, mass.
*   `EnemyArchetypeDA`: Health base, weapon loadout, perception ranges.
*   `MissionDataAsset`: Objectives, dialog lines, rewards.

## 5. Subsystems
We utilize `UGameInstanceSubsystem` and `UWorldSubsystem` to manage global state without cluttering the GameMode or PlayerController.
*   `UQuestSubsystem`: Tracks active missions and objectives.
*   `UPursuitSubsystem`: Manages the "Wanted" level, spawning police vehicles and AI based on heat level.
*   `UTimeWeatherSubsystem`: Manages the day/night cycle and drives the dynamic weather parameters in the SkyAtmosphere/Niagara systems.

## 6. Save System
Implemented using custom `USaveGame` objects serialized to disk.
*   **State Saved:** Player Transform, Inventory, Skill Points, Quest States, World States (which outposts are cleared), Wanted Level, Current Time.
*   **System:** A dedicated `USaveManagerSubsystem` handles async saving/loading to prevent hitches.

## 7. AI & Perception
*   **AIPerceptionComponent:** Used for Sight, Hearing, and Damage detection.
*   **MassEntity (ECS):** Used for ambient city traffic and crowds to allow thousands of agents at low CPU cost.
*   **Behavior Trees:** Used for complex combat AI (flanking, taking cover, retreating).

## 8. Network Architecture
The core architecture uses UE5's replication system macros (`UPROPERTY(Replicated)`, `Server_`, `NetMulticast_`) on key components (Health, Weapon State, Transform). Even though V1 is single-player, this ensures coop/multiplayer can be added without a total rewrite.

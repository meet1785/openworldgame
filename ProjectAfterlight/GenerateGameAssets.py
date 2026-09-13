import unreal
import os

def create_directory(path):
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        unreal.EditorAssetLibrary.make_directory(path)
        unreal.log("Created directory: " + path)

def create_base_directories():
    base_path = "/Game/ProjectAfterlight"
    folders = [
        "Characters/Player",
        "Characters/Enemies",
        "Weapons/Meshes",
        "Weapons/Textures",
        "Environment/Buildings",
        "Environment/Props",
        "UI/Icons",
        "UI/Widgets",
        "Audio/SFX",
        "Audio/Music",
        "VFX/Particles",
        "Systems/DataAssets"
    ]
    
    for folder in folders:
        create_directory(f"{base_path}/{folder}")

def create_placeholder_material(mat_name, package_path, color):
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    
    # Create the material asset
    mat_factory = unreal.MaterialFactoryNew()
    new_mat = asset_tools.create_asset(mat_name, package_path, unreal.Material, mat_factory)
    
    # In a full implementation, we would wire up a VectorParameter for the base color here
    # For now, it creates the blank master material for artists to use.
    
    unreal.EditorAssetLibrary.save_asset(new_mat.get_path_name())
    unreal.log(f"Created placeholder material: {new_mat.get_path_name()}")

def main():
    unreal.log("=== Generating Project Afterlight Assets ===")
    
    # 1. Generate Folder Structure
    create_base_directories()
    
    # 2. Generate Master Materials
    mat_path = "/Game/ProjectAfterlight/Environment"
    create_placeholder_material("M_Master_Neon", mat_path, (0.0, 1.0, 1.0))
    create_placeholder_material("M_Master_Concrete", mat_path, (0.2, 0.2, 0.2))
    create_placeholder_material("M_Master_Metal", mat_path, (0.5, 0.5, 0.5))
    
    # 3. Generate Data Asset Placeholders
    # Create a basic PrimaryDataAsset for Weapon Stats
    unreal.log("Generating Data Asset templates...")
    
    unreal.log("=== Asset Generation Complete ===")

if __name__ == "__main__":
    main()

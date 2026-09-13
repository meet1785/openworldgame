import unreal
import os

def create_directory(path):
    if not unreal.EditorAssetLibrary.does_directory_exist(path):
        unreal.EditorAssetLibrary.make_directory(path)

def create_placeholder_material(name, path, r, g, b):
    asset_path = f"{path}/{name}"
    
    if unreal.EditorAssetLibrary.does_asset_exist(asset_path):
        return
        
    material_factory = unreal.MaterialFactoryNew()
    new_material = unreal.AssetToolsHelpers.get_asset_tools().create_asset(name, path, unreal.Material, material_factory)
    
    # In a full script, we would use Material Editing Library to hook up a VectorParameter for color.
    # For now, this just generates the asset file.
    unreal.EditorAssetLibrary.save_loaded_asset(new_material)
    print(f"Created material: {asset_path}")

def generate_assets():
    print("Starting asset generation for Project Afterlight...")
    
    base_path = "/Game"
    dirs = ["/Characters", "/Weapons", "/Environment", "/UI", "/Audio"]
    
    for d in dirs:
        create_directory(base_path + d)
        
    # Generate Faction Colors
    create_placeholder_material("M_Aegis_Color", "/Game/Environment", 0.0, 0.2, 0.8) # Blue
    create_placeholder_material("M_Rust_Color", "/Game/Environment", 0.8, 0.2, 0.0) # Red
    create_placeholder_material("M_Null_Color", "/Game/Environment", 0.1, 0.8, 0.1) # Green
    
    # Generate placeholder textures using Editor tools if needed
    
    print("Asset generation complete. Please assign these materials to your whitebox meshes.")

if __name__ == "__main__":
    generate_assets()

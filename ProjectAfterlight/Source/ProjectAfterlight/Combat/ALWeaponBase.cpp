#include "Combat/ALWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Net/UnrealNetwork.h"

AALWeaponBase::AALWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	CurrentAmmoInMagazine = WeaponStats.MaxMagazine;
	ReserveAmmo = 120; // Default fallback
}

void AALWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AALWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AALWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AALWeaponBase, CurrentAmmoInMagazine);
	DOREPLIFETIME(AALWeaponBase, ReserveAmmo);
}

void AALWeaponBase::Fire()
{
	if (CurrentAmmoInMagazine > 0)
	{
		if (HasAuthority())
		{
			// Server logic (Spawn projectile / Line Trace)
			CurrentAmmoInMagazine--;
		}
		else
		{
			Server_Fire(); // Request server to fire
			// Client-side effects (muzzle flash, sound, recoil animation)
		}
	}
	else
	{
		// Auto reload or dry fire click
	}
}

bool AALWeaponBase::Server_Fire_Validate()
{
	return true; // Add anti-cheat validation later (rate of fire checks)
}

void AALWeaponBase::Server_Fire_Implementation()
{
	Fire(); // Server executes the actual logic
}

void AALWeaponBase::Reload()
{
	if (ReserveAmmo > 0 && CurrentAmmoInMagazine < WeaponStats.MaxMagazine)
	{
		// Logic to wait for animation/reload time before filling
		int32 AmmoNeeded = WeaponStats.MaxMagazine - CurrentAmmoInMagazine;
		int32 AmmoToLoad = FMath::Min(AmmoNeeded, ReserveAmmo);

		CurrentAmmoInMagazine += AmmoToLoad;
		ReserveAmmo -= AmmoToLoad;
	}
}

bool AALWeaponBase::AddAttachment(AALWeaponAttachmentBase* NewAttachment)
{
	if (!NewAttachment) return false;

	EAttachmentType Type = NewAttachment->AttachmentType;

	// Remove existing attachment of this type if it exists
	if (ActiveAttachments.Contains(Type))
	{
		RemoveAttachment(Type);
	}

	// Attach physically to the weapon mesh
	FName SocketName;
	switch (Type)
	{
		case EAttachmentType::Optic: SocketName = "SightSocket"; break;
		case EAttachmentType::Muzzle: SocketName = "MuzzleSocket"; break;
		case EAttachmentType::Grip: SocketName = "GripSocket"; break;
		default: SocketName = "None"; break;
	}

	NewAttachment->AttachToComponent(WeaponMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	ActiveAttachments.Add(Type, NewAttachment);

	return true;
}

void AALWeaponBase::RemoveAttachment(EAttachmentType Type)
{
	if (ActiveAttachments.Contains(Type))
	{
		AALWeaponAttachmentBase* OldAttachment = ActiveAttachments[Type];
		OldAttachment->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		OldAttachment->Destroy(); // Or return to inventory
		ActiveAttachments.Remove(Type);
	}
}

FWeaponStats AALWeaponBase::GetModifiedStats() const
{
	FWeaponStats ModStats = WeaponStats;

	for (const auto& Pair : ActiveAttachments)
	{
		AALWeaponAttachmentBase* Attachment = Pair.Value;
		if (Attachment)
		{
			ModStats.MaxMagazine += Attachment->ExtraMagazineCapacity;
			// Multiply other stats like recoil and range
		}
	}

	return ModStats;
}

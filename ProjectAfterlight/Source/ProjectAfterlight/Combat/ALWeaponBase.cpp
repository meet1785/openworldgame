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

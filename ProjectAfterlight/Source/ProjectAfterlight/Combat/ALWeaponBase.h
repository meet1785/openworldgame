#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALWeaponBase.generated.h"

class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	Pistol,
	Rifle,
	Shotgun,
	Sniper,
	Melee
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BaseDamage = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMagazine = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ReloadTime = 2.0f;
};

UCLASS()
class PROJECTAFTERLIGHT_API AALWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AALWeaponBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Data")
	EWeaponType WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Data")
	FWeaponStats WeaponStats;

	UPROPERTY(Replicated)
	int32 CurrentAmmoInMagazine;

	UPROPERTY(Replicated)
	int32 ReserveAmmo;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Fire();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_Fire();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void Reload();
};

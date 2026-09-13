#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ALStealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTAFTERLIGHT_API UALStealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UALStealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Stealth")
	void SetStealthMode(bool bIsStealthing);

	UFUNCTION(BlueprintPure, Category = "Stealth")
	bool IsInStealthMode() const { return bIsStealthActive; }

	// Reduces footstep noise range when active
	UFUNCTION(BlueprintPure, Category = "Stealth")
	float GetNoiseModifier() const;

	// Request a stealth takedown on an enemy
	UFUNCTION(BlueprintCallable, Category = "Stealth")
	bool AttemptTakedown(class AALEnemyBase* TargetEnemy);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stealth")
	bool bIsStealthActive;
};

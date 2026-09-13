#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "ALBaseCharacter.generated.h"

class UAbilitySystemComponent;
class UALAttributeSet;

UCLASS()
class PROJECTAFTERLIGHT_API AALBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AALBaseCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void BeginPlay() override;

	// Gameplay Ability System
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	UALAttributeSet* AttributeSet;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Health and Damage hooks
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual float GetMaxHealth() const;
};

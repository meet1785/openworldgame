#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h" // Requires ChaosVehicles Plugin
#include "ALVehicleBase.generated.h"

UCLASS()
class PROJECTAFTERLIGHT_API AALVehicleBase : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:
	AALVehicleBase();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// Input bindings
	void Throttle(float Value);
	void Steering(float Value);
	void Brake(float Value);
	void HandbrakePressed();
	void HandbrakeReleased();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* Camera;
};

#include "Vehicles/ALVehicleBase.h"
#include "ChaosVehicleMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"

AALVehicleBase::AALVehicleBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Base Chaos setup handled by Blueprint subclass
}

void AALVehicleBase::BeginPlay()
{
	Super::BeginPlay();
}

void AALVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Legacy input binding as placeholder, should use EnhancedInput in BP
	PlayerInputComponent->BindAxis("MoveForward", this, &AALVehicleBase::Throttle);
	PlayerInputComponent->BindAxis("MoveRight", this, &AALVehicleBase::Steering);
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &AALVehicleBase::HandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &AALVehicleBase::HandbrakeReleased);
}

void AALVehicleBase::Throttle(float Value)
{
	if (UChaosVehicleMovementComponent* VehicleMovement = Cast<UChaosVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		VehicleMovement->SetThrottleInput(Value);
		VehicleMovement->SetBrakeInput(Value < 0.0f ? -Value : 0.0f); // Simplistic brake mapping
	}
}

void AALVehicleBase::Steering(float Value)
{
	if (UChaosVehicleMovementComponent* VehicleMovement = Cast<UChaosVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		VehicleMovement->SetSteeringInput(Value);
	}
}

void AALVehicleBase::Brake(float Value)
{
	if (UChaosVehicleMovementComponent* VehicleMovement = Cast<UChaosVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		VehicleMovement->SetBrakeInput(Value);
	}
}

void AALVehicleBase::HandbrakePressed()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = Cast<UChaosVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		VehicleMovement->SetHandbrakeInput(true);
	}
}

void AALVehicleBase::HandbrakeReleased()
{
	if (UChaosVehicleMovementComponent* VehicleMovement = Cast<UChaosVehicleMovementComponent>(GetVehicleMovementComponent()))
	{
		VehicleMovement->SetHandbrakeInput(false);
	}
}

#include "Systems/ALPursuitSubsystem.h"
#include "Engine/World.h"

void UALPursuitSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentWantedLevel = 0;
	HeatValue = 0.f;
	UE_LOG(LogTemp, Log, TEXT("Pursuit Subsystem Initialized."));
}

void UALPursuitSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UALPursuitSubsystem::IncreaseWantedLevel(int32 Amount)
{
	CurrentWantedLevel = FMath::Clamp(CurrentWantedLevel + Amount, 0, 5);
	DispatchUnits();
}

void UALPursuitSubsystem::DecreaseWantedLevel(int32 Amount)
{
	CurrentWantedLevel = FMath::Clamp(CurrentWantedLevel - Amount, 0, 5);
}

void UALPursuitSubsystem::ReportCrime(FVector Location, AActor* Suspect)
{
	// Logic to evaluate crime severity and increase heat/wanted level
	HeatValue += 10.0f; // Example arbitrary value
	
	if (HeatValue > 100.0f && CurrentWantedLevel < 5)
	{
		HeatValue = 0.0f;
		IncreaseWantedLevel(1);
	}
	
	// Notify AI director to spawn or route units to Location
}

void UALPursuitSubsystem::DispatchUnits()
{
	if (CurrentWantedLevel == 0) return;

	// Depending on level, spawn different archetype configurations:
	// Lvl 1: Local Patrol (2 units)
	// Lvl 2: Multiple Interceptors (4 units)
	// Lvl 3: SWAT/Armored Response
	// Lvl 4: Air Support (Drones/Helicopter)
	// Lvl 5: Military/Elite Task Force
}

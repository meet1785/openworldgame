#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ALPursuitSubsystem.generated.h"

UCLASS()
class PROJECTAFTERLIGHT_API UALPursuitSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Heat Level (0 = None, 5 = Max)
	UFUNCTION(BlueprintCallable, Category = "Pursuit")
	void IncreaseWantedLevel(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Pursuit")
	void DecreaseWantedLevel(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Pursuit")
	int32 GetCurrentWantedLevel() const { return CurrentWantedLevel; }

	// Triggered when a crime is witnessed
	UFUNCTION(BlueprintCallable, Category = "Pursuit")
	void ReportCrime(FVector Location, AActor* Suspect);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pursuit State")
	int32 CurrentWantedLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pursuit State")
	float HeatValue;

	// Internal logic to dispatch police/factions
	void DispatchUnits();
};

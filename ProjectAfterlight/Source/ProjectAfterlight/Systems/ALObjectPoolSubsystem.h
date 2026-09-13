#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ALObjectPoolSubsystem.generated.h"

class AActor;

UCLASS()
class PROJECTAFTERLIGHT_API UALObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// Request an actor from the pool, spawns one if none are available
	UFUNCTION(BlueprintCallable, Category = "Optimization|Pooling")
	AActor* AcquireActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform);

	// Return an actor to the pool, disabling it instead of destroying
	UFUNCTION(BlueprintCallable, Category = "Optimization|Pooling")
	void ReturnActor(AActor* ActorToReturn);

protected:
	// Maps a class type to an array of available (hidden/deactivated) actors
	UPROPERTY()
	TMap<UClass*, TArray<AActor*>> ActorPool;

private:
	void SetActorActiveState(AActor* Actor, bool bIsActive);
};

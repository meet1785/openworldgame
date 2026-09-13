#include "Systems/ALObjectPoolSubsystem.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

void UALObjectPoolSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

AActor* UALObjectPoolSubsystem::AcquireActor(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform)
{
	if (!ActorClass) return nullptr;

	UClass* ClassKey = ActorClass.Get();
	
	if (ActorPool.Contains(ClassKey) && ActorPool[ClassKey].Num() > 0)
	{
		// Pop the last available actor
		AActor* PooledActor = ActorPool[ClassKey].Pop();
		
		PooledActor->SetActorTransform(SpawnTransform);
		SetActorActiveState(PooledActor, true);
		
		return PooledActor;
	}

	// Pool is empty for this class, spawn a new one
	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		return World->SpawnActor<AActor>(ActorClass, SpawnTransform, SpawnParams);
	}

	return nullptr;
}

void UALObjectPoolSubsystem::ReturnActor(AActor* ActorToReturn)
{
	if (!ActorToReturn) return;

	UClass* ClassKey = ActorToReturn->GetClass();
	
	SetActorActiveState(ActorToReturn, false);
	
	if (!ActorPool.Contains(ClassKey))
	{
		ActorPool.Add(ClassKey, TArray<AActor*>());
	}
	
	ActorPool[ClassKey].Add(ActorToReturn);
}

void UALObjectPoolSubsystem::SetActorActiveState(AActor* Actor, bool bIsActive)
{
	if (!Actor) return;

	Actor->SetActorHiddenInGame(!bIsActive);
	Actor->SetActorEnableCollision(bIsActive);
	Actor->SetActorTickEnabled(bIsActive);
}

#include "Characters/ALStealthComponent.h"
#include "AI/ALEnemyBase.h"

UALStealthComponent::UALStealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bIsStealthActive = false;
}

void UALStealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UALStealthComponent::SetStealthMode(bool bIsStealthing)
{
	bIsStealthActive = bIsStealthing;
}

float UALStealthComponent::GetNoiseModifier() const
{
	return bIsStealthActive ? 0.3f : 1.0f; // 70% reduction in noise while sneaking
}

bool UALStealthComponent::AttemptTakedown(AALEnemyBase* TargetEnemy)
{
	if (!TargetEnemy) return false;

	// Check if enemy is unaware
	if (!TargetEnemy->IsAwareOfPlayer())
	{
		TargetEnemy->ReceiveTakedown();
		return true;
	}
	
	return false; // Failed, enemy turned around or saw player
}

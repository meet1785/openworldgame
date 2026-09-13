#include "Progression/ALProgressionComponent.h"

UALProgressionComponent::UALProgressionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentLevel = 1;
	CurrentXP = 0;
	AvailableSkillPoints = 0;
	MaxLevel = 50;
}

void UALProgressionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UALProgressionComponent::AddExperience(int32 Amount)
{
	if (CurrentLevel >= MaxLevel || Amount <= 0) return;

	CurrentXP += Amount;
	OnXPChanged.Broadcast(CurrentXP);

	CheckLevelUp();
}

void UALProgressionComponent::CheckLevelUp()
{
	int32 XPRequired = GetRequiredXPForLevel(CurrentLevel + 1);

	while (CurrentXP >= XPRequired && CurrentLevel < MaxLevel)
	{
		CurrentXP -= XPRequired; // Carry over excess XP
		CurrentLevel++;
		AvailableSkillPoints++; // Award 1 point per level

		OnLevelUp.Broadcast(CurrentLevel, AvailableSkillPoints);
		XPRequired = GetRequiredXPForLevel(CurrentLevel + 1);
	}
}

int32 UALProgressionComponent::GetRequiredXPForLevel(int32 Level) const
{
	// Simple exponential XP curve: Base * (Level^1.5)
	return FMath::FloorToInt(1000.0f * FMath::Pow(static_cast<float>(Level), 1.5f));
}

bool UALProgressionComponent::SpendSkillPoint()
{
	if (AvailableSkillPoints > 0)
	{
		AvailableSkillPoints--;
		return true;
	}
	return false;
}

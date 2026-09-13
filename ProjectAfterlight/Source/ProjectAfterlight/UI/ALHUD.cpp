#include "UI/ALHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UALHUD::NativeConstruct()
{
	Super::NativeConstruct();
}

void UALHUD::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	if (HealthBar && MaxHealth > 0.0f)
	{
		HealthBar->SetPercent(CurrentHealth / MaxHealth);
	}
}

void UALHUD::UpdateAmmo(int32 CurrentAmmo, int32 ReserveAmmo)
{
	if (AmmoText)
	{
		FString AmmoString = FString::Printf(TEXT("%d / %d"), CurrentAmmo, ReserveAmmo);
		AmmoText->SetText(FText::FromString(AmmoString));
	}
}

void UALHUD::UpdateWantedLevel(int32 WantedLevel)
{
	if (WantedLevelText)
	{
		FString WantedString = (WantedLevel > 0) ? FString::Printf(TEXT("WANTED: %d"), WantedLevel) : TEXT("");
		WantedLevelText->SetText(FText::FromString(WantedString));
		
		// Could trigger animation/color changes here
	}
}

void UALHUD::ShowQuestNotification(const FText& QuestName, const FText& Status)
{
	// Trigger Blueprint animations to slide in a notification panel
	UE_LOG(LogTemp, Log, TEXT("QUEST UPDATE: %s - %s"), *QuestName.ToString(), *Status.ToString());
}

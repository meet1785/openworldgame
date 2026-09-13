#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ALHUD.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class PROJECTAFTERLIGHT_API UALHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Update UI Hooks
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateAmmo(int32 CurrentAmmo, int32 ReserveAmmo);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateWantedLevel(int32 WantedLevel);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowQuestNotification(const FText& QuestName, const FText& Status);

protected:
	virtual void NativeConstruct() override;

	// Binds to Blueprint widgets with the exact same names
	UPROPERTY(meta = (BindWidgetOptional))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* AmmoText;

	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* WantedLevelText;
};

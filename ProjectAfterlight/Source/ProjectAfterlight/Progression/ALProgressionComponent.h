#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ALProgressionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLevelUp, int32, NewLevel, int32, SkillPointsAwarded);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnXPChanged, int32, CurrentXP);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTAFTERLIGHT_API UALProgressionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UALProgressionComponent();

	UPROPERTY(BlueprintAssignable, Category = "Progression")
	FOnLevelUp OnLevelUp;

	UPROPERTY(BlueprintAssignable, Category = "Progression")
	FOnXPChanged OnXPChanged;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	void AddExperience(int32 Amount);

	UFUNCTION(BlueprintPure, Category = "Progression")
	int32 GetRequiredXPForLevel(int32 Level) const;

	UFUNCTION(BlueprintCallable, Category = "Progression")
	bool SpendSkillPoint();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 CurrentLevel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 CurrentXP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Progression")
	int32 AvailableSkillPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Progression")
	int32 MaxLevel;

private:
	void CheckLevelUp();
};

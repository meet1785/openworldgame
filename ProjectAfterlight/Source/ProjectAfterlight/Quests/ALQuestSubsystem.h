#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Quests/ALQuestBase.h"
#include "ALQuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStateChanged, UALQuestBase*, Quest);

UCLASS()
class PROJECTAFTERLIGHT_API UALQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(BlueprintAssignable, Category = "Quests")
	FOnQuestStateChanged OnQuestStateChanged;

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void StartQuest(TSubclassOf<UALQuestBase> QuestClass);

	UFUNCTION(BlueprintCallable, Category = "Quests")
	void UpdateQuestObjective(FName QuestID, int32 ObjectiveIndex, int32 Amount = 1);

	UFUNCTION(BlueprintPure, Category = "Quests")
	UALQuestBase* GetActiveQuestByID(FName QuestID) const;

	UFUNCTION(BlueprintPure, Category = "Quests")
	const TArray<UALQuestBase*>& GetActiveQuests() const { return ActiveQuests; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quests")
	TArray<UALQuestBase*> ActiveQuests;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quests")
	TArray<UALQuestBase*> CompletedQuests;
};

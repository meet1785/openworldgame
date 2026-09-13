#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ALQuestBase.generated.h"

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	NotStarted,
	InProgress,
	Completed,
	Failed
};

USTRUCT(BlueprintType)
struct FALObjective
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsCompleted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RequiredAmount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentAmount = 0;
};

UCLASS(Blueprintable, BlueprintType)
class PROJECTAFTERLIGHT_API UALQuestBase : public UObject
{
	GENERATED_BODY()
	
public:
	UALQuestBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText QuestDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	EQuestState CurrentState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
	TArray<FALObjective> Objectives;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void UpdateObjective(int32 ObjectiveIndex, int32 Amount = 1);

	UFUNCTION(BlueprintPure, Category = "Quest")
	bool AreAllObjectivesComplete() const;
};

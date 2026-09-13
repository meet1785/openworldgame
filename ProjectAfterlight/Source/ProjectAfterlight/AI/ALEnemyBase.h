#pragma once

#include "CoreMinimal.h"
#include "Characters/ALBaseCharacter.h"
#include "Perception/AIPerceptionTypes.h"
#include "ALEnemyBase.generated.h"

class UBehaviorTree;
class UAIPerceptionComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Hearing;
class UAISenseConfig_Damage;

UCLASS()
class PROJECTAFTERLIGHT_API AALEnemyBase : public AALBaseCharacter
{
	GENERATED_BODY()

public:
	AALEnemyBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	UAIPerceptionComponent* AIPerception;

	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY()
	UAISenseConfig_Hearing* HearingConfig;

	UPROPERTY()
	UAISenseConfig_Damage* DamageConfig;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

public:
	UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
};

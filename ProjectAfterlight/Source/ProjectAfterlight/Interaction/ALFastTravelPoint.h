#pragma once

#include "CoreMinimal.h"
#include "Interaction/ALInteractableActor.h"
#include "ALFastTravelPoint.generated.h"

UCLASS()
class PROJECTAFTERLIGHT_API AALFastTravelPoint : public AALInteractableActor
{
	GENERATED_BODY()
	
public:
	AALFastTravelPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fast Travel")
	FName LocationID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fast Travel")
	FText LocationName;

	virtual void Interact_Implementation(class AALPlayerCharacter* InteractingCharacter) override;

protected:
	virtual void BeginPlay() override;

	// Checks if the player has unlocked this point previously
	bool bIsUnlocked;
};

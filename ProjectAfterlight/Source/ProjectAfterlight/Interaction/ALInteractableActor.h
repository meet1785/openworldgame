#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ALInteractableInterface.h"
#include "ALInteractableActor.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTAFTERLIGHT_API AALInteractableActor : public AActor, public IALInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AALInteractableActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractionBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractionPromptText;

public:	
	virtual void Tick(float DeltaTime) override;

	// IALInteractableInterface Implementation
	virtual FText GetInteractionPrompt_Implementation() const override;
	virtual void Interact_Implementation(class AALPlayerCharacter* InteractingCharacter) override;
	virtual bool CanInteract_Implementation() const override;
};

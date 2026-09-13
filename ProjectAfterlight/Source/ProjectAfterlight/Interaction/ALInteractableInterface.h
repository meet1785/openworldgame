#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ALInteractableInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UALInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

class PROJECTAFTERLIGHT_API IALInteractableInterface
{
	GENERATED_BODY()

public:
	// Returns the prompt to display on the UI (e.g., "Press E to Pick Up")
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText GetInteractionPrompt() const;

	// Called when the player successfully interacts
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(class AALPlayerCharacter* InteractingCharacter);

	// Determines if this object can currently be interacted with
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	bool CanInteract() const;
};

#include "Interaction/ALFastTravelPoint.h"
#include "Characters/ALPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

AALFastTravelPoint::AALFastTravelPoint()
{
	bIsUnlocked = false;
	InteractionPromptText = FText::FromString("Fast Travel");
}

void AALFastTravelPoint::BeginPlay()
{
	Super::BeginPlay();
	
	// Check SaveGame data here to see if LocationID is unlocked
}

void AALFastTravelPoint::Interact_Implementation(AALPlayerCharacter* InteractingCharacter)
{
	Super::Interact_Implementation(InteractingCharacter);

	if (!bIsUnlocked)
	{
		bIsUnlocked = true;
		UE_LOG(LogTemp, Log, TEXT("Unlocked Fast Travel Point: %s"), *LocationName.ToString());
		// Save unlocked state
		return;
	}

	// Trigger UI Map to open and select destination, or teleport directly for debug
	UE_LOG(LogTemp, Log, TEXT("Opening Fast Travel UI at %s"), *LocationName.ToString());
}

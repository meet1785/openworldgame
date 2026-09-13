#include "Interaction/ALInteractableActor.h"
#include "Components/BoxComponent.h"
#include "Characters/ALPlayerCharacter.h"

AALInteractableActor::AALInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	RootComponent = InteractionBox;
	InteractionBox->SetBoxExtent(FVector(100.f, 100.f, 100.f));

	InteractionPromptText = FText::FromString("Interact");
}

void AALInteractableActor::BeginPlay()
{
	Super::BeginPlay();
}

void AALInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FText AALInteractableActor::GetInteractionPrompt_Implementation() const
{
	return InteractionPromptText;
}

void AALInteractableActor::Interact_Implementation(AALPlayerCharacter* InteractingCharacter)
{
	UE_LOG(LogTemp, Log, TEXT("Interacted with %s"), *GetName());
	// Override in child classes (Pickups, Doors, NPCs)
}

bool AALInteractableActor::CanInteract_Implementation() const
{
	return true; // Override to add logic (e.g., locked doors return false)
}

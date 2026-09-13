#include "Core/AfterlightGameMode.h"
#include "Core/ALPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AAfterlightGameMode::AAfterlightGameMode()
{
	PlayerControllerClass = AALPlayerController::StaticClass();
	
	// Set default pawn class to our character BP later
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Player/BP_PlayerCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}

void AAfterlightGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize high-level game logic here
}

void AAfterlightGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	// Handle loading state, pre-game initialization
}

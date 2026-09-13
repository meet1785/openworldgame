#include "Core/ALCheatManager.h"
#include "Engine/World.h"
#include "Systems/ALPursuitSubsystem.h"
#include "Characters/ALPlayerCharacter.h"
#include "GameFramework/PlayerController.h"

void UALCheatManager::GiveMoney(int32 Amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Cheat: Gave player %d credits."), Amount);
	// In a full implementation, grab the player's inventory or save data and add money
}

void UALCheatManager::SetWantedLevel(int32 Level)
{
	if (UWorld* World = GetWorld())
	{
		if (UALPursuitSubsystem* PursuitSub = World->GetSubsystem<UALPursuitSubsystem>())
		{
			// Reset to 0 then increase to exact level
			PursuitSub->DecreaseWantedLevel(5); 
			PursuitSub->IncreaseWantedLevel(Level);
			UE_LOG(LogTemp, Warning, TEXT("Cheat: Set Wanted Level to %d."), Level);
		}
	}
}

void UALCheatManager::TeleportToSafehouse()
{
	if (APlayerController* PC = GetOuterAPlayerController())
	{
		if (AALPlayerCharacter* Player = Cast<AALPlayerCharacter>(PC->GetPawn()))
		{
			// Hardcoded vector for debug safehouse
			Player->SetActorLocation(FVector(0, 0, 1000));
			UE_LOG(LogTemp, Warning, TEXT("Cheat: Teleported to Safehouse."));
		}
	}
}

void UALCheatManager::GodMode()
{
	UE_LOG(LogTemp, Warning, TEXT("Cheat: God Mode Toggled."));
	// Grab ALBaseCharacter Attribute set and lock health at MaxHealth
}

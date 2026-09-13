#include "SaveSystem/ALSaveManagerSubsystem.h"
#include "SaveSystem/ALSaveGame.h"
#include "Kismet/GameplayStatics.h"

void UALSaveManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSaveGame = Cast<UALSaveGame>(UGameplayStatics::CreateSaveGameObject(UALSaveGame::StaticClass()));
}

void UALSaveManagerSubsystem::SaveGameAsync(const FString& SlotName)
{
	if (!CurrentSaveGame) return;

	CurrentSaveGame->SaveSlotName = SlotName;
	
	// Delegate binding for async save
	FAsyncSaveGameToSlotDelegate SavedDelegate;
	SavedDelegate.BindUObject(this, &UALSaveManagerSubsystem::SaveGameDelegate);

	UGameplayStatics::AsyncSaveGameToSlot(CurrentSaveGame, SlotName, 0, SavedDelegate);
}

void UALSaveManagerSubsystem::LoadGameAsync(const FString& SlotName)
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &UALSaveManagerSubsystem::LoadGameDelegate);

	UGameplayStatics::AsyncLoadGameFromSlot(SlotName, 0, LoadedDelegate);
}

void UALSaveManagerSubsystem::SaveGameDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	if (bSuccess)
	{
		UE_LOG(LogTemp, Log, TEXT("Game Saved Successfully to slot: %s"), *SlotName);
	}
	OnGameSaved.Broadcast(bSuccess);
}

void UALSaveManagerSubsystem::LoadGameDelegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	if (LoadedGameData)
	{
		CurrentSaveGame = Cast<UALSaveGame>(LoadedGameData);
		UE_LOG(LogTemp, Log, TEXT("Game Loaded Successfully from slot: %s"), *SlotName);
		OnGameLoaded.Broadcast(true);
		
		// Here we would typically dispatch events to the Player Character, Quest System, etc. to restore state.
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load game from slot: %s"), *SlotName);
		OnGameLoaded.Broadcast(false);
	}
}

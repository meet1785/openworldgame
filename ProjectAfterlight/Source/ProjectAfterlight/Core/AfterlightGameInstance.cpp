#include "Core/AfterlightGameInstance.h"

void UAfterlightGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Log, TEXT("Afterlight GameInstance Initialized."));
}

void UAfterlightGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UAfterlightGameInstance::LoadGame(const FString& SlotName)
{
	// TODO: Implement USaveGame serialization integration
}

void UAfterlightGameInstance::SaveGame(const FString& SlotName)
{
	// TODO: Implement USaveGame serialization integration
}

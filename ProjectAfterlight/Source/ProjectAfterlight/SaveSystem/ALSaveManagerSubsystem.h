#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ALSaveManagerSubsystem.generated.h"

class UALSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameSaved, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameLoaded, bool, bSuccess);

UCLASS()
class PROJECTAFTERLIGHT_API UALSaveManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(BlueprintAssignable, Category = "SaveSystem")
	FOnGameSaved OnGameSaved;

	UPROPERTY(BlueprintAssignable, Category = "SaveSystem")
	FOnGameLoaded OnGameLoaded;

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void SaveGameAsync(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void LoadGameAsync(const FString& SlotName);

	UFUNCTION(BlueprintPure, Category = "SaveSystem")
	UALSaveGame* GetCurrentSaveGame() const { return CurrentSaveGame; }

protected:
	UPROPERTY()
	UALSaveGame* CurrentSaveGame;

private:
	void SaveGameDelegate(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	void LoadGameDelegate(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);
};

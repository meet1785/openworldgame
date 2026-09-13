#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AfterlightGameInstance.generated.h"

UCLASS()
class PROJECTAFTERLIGHT_API UAfterlightGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

	// Load Game/Save Game API
	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void LoadGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveSystem")
	void SaveGame(const FString& SlotName);
};

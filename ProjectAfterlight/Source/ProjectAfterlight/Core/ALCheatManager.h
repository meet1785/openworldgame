#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "ALCheatManager.generated.h"

UCLASS()
class PROJECTAFTERLIGHT_API UALCheatManager : public UCheatManager
{
	GENERATED_BODY()
	
public:
	// Console command: AL.GiveMoney 1000
	UFUNCTION(exec)
	void GiveMoney(int32 Amount);

	// Console command: AL.SetWantedLevel 3
	UFUNCTION(exec)
	void SetWantedLevel(int32 Level);

	// Console command: AL.TeleportToSafehouse
	UFUNCTION(exec)
	void TeleportToSafehouse();

	// Console command: AL.GodMode
	UFUNCTION(exec)
	void GodMode();
};

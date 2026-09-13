#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AfterlightGameMode.generated.h"

UCLASS()
class PROJECTAFTERLIGHT_API AAfterlightGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAfterlightGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
};

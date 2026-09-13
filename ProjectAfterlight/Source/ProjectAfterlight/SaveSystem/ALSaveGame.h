#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ALSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FALPlayerSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform PlayerTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Credits = 0;

	// Add Skill points, inventory raw data etc.
};

USTRUCT(BlueprintType)
struct FALWorldSaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeOfDay = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, bool> ClearedOutposts;
};

UCLASS()
class PROJECTAFTERLIGHT_API UALSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FALPlayerSaveData PlayerData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FALWorldSaveData WorldData;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveData")
	uint32 UserIndex;
};

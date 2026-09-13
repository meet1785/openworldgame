#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Dialogue/ALDialogueTypes.h"
#include "ALDialogueSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueLinePlayed, const FALDialogueLine&, Line);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

UCLASS()
class PROJECTAFTERLIGHT_API UALDialogueSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueLinePlayed OnDialogueLinePlayed;

	UPROPERTY(BlueprintAssignable, Category = "Dialogue")
	FOnDialogueEnded OnDialogueEnded;

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartConversation(UDataTable* DialogueTable, FName StartingLineID);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void PlayNextLine();

protected:
	UPROPERTY()
	UDataTable* CurrentDialogueTable;

	FName CurrentLineID;

	FTimerHandle DialogueTimerHandle;
};

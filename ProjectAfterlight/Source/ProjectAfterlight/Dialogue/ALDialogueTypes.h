#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ALDialogueTypes.generated.h"

USTRUCT(BlueprintType)
struct FALDialogueLine : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DialogueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AudioLine = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NextLineID; // "None" if it's the end of the conversation
};

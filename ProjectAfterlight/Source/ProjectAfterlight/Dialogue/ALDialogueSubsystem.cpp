#include "Dialogue/ALDialogueSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

void UALDialogueSubsystem::StartConversation(UDataTable* DialogueTable, FName StartingLineID)
{
	if (!DialogueTable) return;

	CurrentDialogueTable = DialogueTable;
	CurrentLineID = StartingLineID;

	PlayNextLine();
}

void UALDialogueSubsystem::PlayNextLine()
{
	if (!CurrentDialogueTable || CurrentLineID.IsNone())
	{
		OnDialogueEnded.Broadcast();
		CurrentDialogueTable = nullptr;
		return;
	}

	FALDialogueLine* LineData = CurrentDialogueTable->FindRow<FALDialogueLine>(CurrentLineID, TEXT("DialogueSubsystem"));
	
	if (LineData)
	{
		OnDialogueLinePlayed.Broadcast(*LineData);

		// Play Audio
		if (LineData->AudioLine)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), LineData->AudioLine);
		}

		// Prepare next line
		CurrentLineID = LineData->NextLineID;

		// Set timer to auto-advance if it's not a player choice (omitted complex choice logic for brevity)
		GetWorld()->GetTimerManager().SetTimer(DialogueTimerHandle, this, &UALDialogueSubsystem::PlayNextLine, LineData->Duration, false);
	}
	else
	{
		OnDialogueEnded.Broadcast();
	}
}

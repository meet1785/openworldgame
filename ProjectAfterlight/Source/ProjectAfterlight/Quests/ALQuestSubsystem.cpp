#include "Quests/ALQuestSubsystem.h"

void UALQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UALQuestSubsystem::StartQuest(TSubclassOf<UALQuestBase> QuestClass)
{
	if (!QuestClass) return;

	UALQuestBase* NewQuest = NewObject<UALQuestBase>(this, QuestClass);
	if (NewQuest)
	{
		NewQuest->CurrentState = EQuestState::InProgress;
		ActiveQuests.Add(NewQuest);
		OnQuestStateChanged.Broadcast(NewQuest);
	}
}

void UALQuestSubsystem::UpdateQuestObjective(FName QuestID, int32 ObjectiveIndex, int32 Amount)
{
	UALQuestBase* Quest = GetActiveQuestByID(QuestID);
	if (Quest && Quest->CurrentState == EQuestState::InProgress)
	{
		Quest->UpdateObjective(ObjectiveIndex, Amount);

		if (Quest->CurrentState == EQuestState::Completed)
		{
			ActiveQuests.Remove(Quest);
			CompletedQuests.Add(Quest);
			// Reward logic could be triggered here
		}

		OnQuestStateChanged.Broadcast(Quest);
	}
}

UALQuestBase* UALQuestSubsystem::GetActiveQuestByID(FName QuestID) const
{
	for (UALQuestBase* Quest : ActiveQuests)
	{
		if (Quest && Quest->QuestID == QuestID)
		{
			return Quest;
		}
	}
	return nullptr;
}

#include "Quests/ALQuestBase.h"

UALQuestBase::UALQuestBase()
{
	CurrentState = EQuestState::NotStarted;
}

void UALQuestBase::UpdateObjective(int32 ObjectiveIndex, int32 Amount)
{
	if (Objectives.IsValidIndex(ObjectiveIndex) && !Objectives[ObjectiveIndex].bIsCompleted)
	{
		Objectives[ObjectiveIndex].CurrentAmount += Amount;
		
		if (Objectives[ObjectiveIndex].CurrentAmount >= Objectives[ObjectiveIndex].RequiredAmount)
		{
			Objectives[ObjectiveIndex].CurrentAmount = Objectives[ObjectiveIndex].RequiredAmount;
			Objectives[ObjectiveIndex].bIsCompleted = true;
		}

		if (AreAllObjectivesComplete())
		{
			CurrentState = EQuestState::Completed;
		}
	}
}

bool UALQuestBase::AreAllObjectivesComplete() const
{
	for (const FALObjective& Objective : Objectives)
	{
		if (!Objective.bIsCompleted)
		{
			return false;
		}
	}
	return true;
}

#include "AI/ALEnemyBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "BehaviorTree/BehaviorTree.h"

AALEnemyBase::AALEnemyBase()
{
	AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 2000.f;
	SightConfig->LoseSightRadius = 2500.f;
	SightConfig->PeripheralVisionAngleDegrees = 90.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
	HearingConfig->HearingRange = 3000.f;
	HearingConfig->DetectionByAffiliation.bDetectEnemies = true;

	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));

	AIPerception->ConfigureSense(*SightConfig);
	AIPerception->ConfigureSense(*HearingConfig);
	AIPerception->ConfigureSense(*DamageConfig);
	AIPerception->SetDominantSense(SightConfig->GetSenseID());

	AIPerception->OnTargetPerceptionUpdated.AddDynamic(this, &AALEnemyBase::OnTargetPerceptionUpdated);
}

void AALEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AALEnemyBase::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	// Send data to Blackboard via AIController
	if (Stimulus.WasSuccessfullySensed())
	{
		bIsAwareOfPlayer = true;
		// Set Blackboard Key "TargetActor"
	}
	else
	{
		// Lost sight/sound of target
		// Note: AI usually stays aware for a while after losing sight. This is simplified.
		// bIsAwareOfPlayer = false; 
		// Update Blackboard Key "LastKnownLocation"
	}
}

void AALEnemyBase::ReceiveTakedown()
{
	UE_LOG(LogTemp, Warning, TEXT("%s was taken down stealthily!"), *GetName());
	
	// Trigger death animation, disable collision, disable AI logic
	if (AIPerception)
	{
		AIPerception->Deactivate();
	}
	
	// Set health to 0 or destroy after anim
}

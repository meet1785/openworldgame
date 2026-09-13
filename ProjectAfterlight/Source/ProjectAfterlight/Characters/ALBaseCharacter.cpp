#include "Characters/ALBaseCharacter.h"
#include "AbilitySystemComponent.h"
// #include "Systems/ALAttributeSet.h"

AALBaseCharacter::AALBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// AttributeSet = CreateDefaultSubobject<UALAttributeSet>(TEXT("AttributeSet"));
}

UAbilitySystemComponent* AALBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AALBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AALBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AALBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AALBaseCharacter::GetHealth() const
{
	// if (AttributeSet) return AttributeSet->GetHealth();
	return 100.f; // Fallback for now
}

float AALBaseCharacter::GetMaxHealth() const
{
	// if (AttributeSet) return AttributeSet->GetMaxHealth();
	return 100.f; // Fallback for now
}

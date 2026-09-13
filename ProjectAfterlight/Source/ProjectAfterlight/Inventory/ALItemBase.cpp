#include "Inventory/ALItemBase.h"
#include "Characters/ALPlayerCharacter.h"

UALItemBase::UALItemBase()
{
	Quantity = 1;
}

void UALItemBase::Use_Implementation(AALPlayerCharacter* Character)
{
	// Base implementation does nothing. Override in blueprints for specific effects.
	UE_LOG(LogTemp, Warning, TEXT("Used item: %s"), *ItemData.ItemName.ToString());
}

#include "Inventory/ALInventoryComponent.h"
#include "Inventory/ALItemBase.h"

UALInventoryComponent::UALInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	Capacity = 50;
	MaxWeight = 100.0f;
}

void UALInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UALInventoryComponent::AddItem(UALItemBase* Item, int32 Amount)
{
	if (!Item || Amount <= 0) return false;

	// Check capacity
	if (Items.Num() >= Capacity) return false;

	// Check if we already have it to stack
	for (UALItemBase* ExistingItem : Items)
	{
		if (ExistingItem && ExistingItem->GetClass() == Item->GetClass())
		{
			if (ExistingItem->Quantity + Amount <= ExistingItem->ItemData.MaxStackSize)
			{
				ExistingItem->Quantity += Amount;
				OnInventoryUpdated.Broadcast();
				return true;
			}
		}
	}

	// Create new item instance if not stacked
	UALItemBase* NewItem = NewObject<UALItemBase>(this, Item->GetClass());
	NewItem->Quantity = Amount;
	Items.Add(NewItem);
	
	OnInventoryUpdated.Broadcast();
	return true;
}

bool UALInventoryComponent::RemoveItem(UALItemBase* Item, int32 Amount)
{
	if (!Item || Amount <= 0) return false;

	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i] && Items[i]->GetClass() == Item->GetClass())
		{
			Items[i]->Quantity -= Amount;
			if (Items[i]->Quantity <= 0)
			{
				Items.RemoveAt(i);
			}
			OnInventoryUpdated.Broadcast();
			return true;
		}
	}

	return false;
}

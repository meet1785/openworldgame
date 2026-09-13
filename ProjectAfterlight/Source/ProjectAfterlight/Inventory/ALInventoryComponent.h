#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ALInventoryComponent.generated.h"

class UALItemBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTAFTERLIGHT_API UALInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UALInventoryComponent();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventoryUpdated OnInventoryUpdated;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UALItemBase* Item, int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(UALItemBase* Item, int32 Amount = 1);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	const TArray<UALItemBase*>& GetItems() const { return Items; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	TArray<UALItemBase*> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	int32 Capacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	float MaxWeight;
		
};

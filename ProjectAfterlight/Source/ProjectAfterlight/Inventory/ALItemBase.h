#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ALItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Consumable,
	Weapon,
	QuestItem,
	Material
};

USTRUCT(BlueprintType)
struct FALItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight = 0.0f;
};

UCLASS(Blueprintable, BlueprintType, EditInlineNew)
class PROJECTAFTERLIGHT_API UALItemBase : public UObject
{
	GENERATED_BODY()
	
public:
	UALItemBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Data")
	FALItemData ItemData;

	// Used for instances of items
	UPROPERTY(BlueprintReadWrite, Category = "Item Data")
	int32 Quantity;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item")
	void Use(class AALPlayerCharacter* Character);
};

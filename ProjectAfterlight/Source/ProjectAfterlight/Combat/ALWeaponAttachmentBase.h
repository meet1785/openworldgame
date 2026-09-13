#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ALWeaponAttachmentBase.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class EAttachmentType : uint8
{
	Optic,
	Muzzle,
	Grip,
	Magazine
};

UCLASS()
class PROJECTAFTERLIGHT_API AALWeaponAttachmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AALWeaponAttachmentBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attachment")
	EAttachmentType AttachmentType;

	// Modifiers to apply to the base weapon stats
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attachment|Modifiers")
	float RecoilModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attachment|Modifiers")
	float RangeModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attachment|Modifiers")
	int32 ExtraMagazineCapacity = 0;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* AttachmentMesh;

};

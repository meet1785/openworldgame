#include "Combat/ALWeaponAttachmentBase.h"
#include "Components/StaticMeshComponent.h"

AALWeaponAttachmentBase::AALWeaponAttachmentBase()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	AttachmentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AttachmentMesh"));
	RootComponent = AttachmentMesh;
}

void AALWeaponAttachmentBase::BeginPlay()
{
	Super::BeginPlay();
}

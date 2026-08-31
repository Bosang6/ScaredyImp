
#include "Checkpoint/VoidVolume.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/VoidRecoverable.h"

// Sets default values
AVoidVolume::AVoidVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	VoidBox = CreateDefaultSubobject<UBoxComponent>(TEXT("VoidBox"));
	VoidBox->SetupAttachment(Root);
	VoidBox->SetBoxExtent(FVector(500.0f, 500.0f, 100.0f));
	VoidBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	VoidBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	VoidBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	VoidBox->SetGenerateOverlapEvents(true);
	VoidBox->OnComponentBeginOverlap.AddDynamic(this, &AVoidVolume::OnVoidBeginOverlap);


}

void AVoidVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVoidVolume::OnVoidBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(OtherActor)) return;

	if (OtherActor->Implements<UVoidRecoverable>())
	{
		IVoidRecoverable::Execute_HandleVoid(OtherActor);
	}
}



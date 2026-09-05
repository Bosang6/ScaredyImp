

#include "Checkpoint/Portal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ArrowComponent.h"
#include "ScaredyImpCharacter.h"

APortal::APortal()
{
	PrimaryActorTick.bCanEverTick = false;

	PortalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PortalMesh"));
	SetRootComponent(PortalMesh);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(PortalMesh);
	Trigger->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Trigger->SetGenerateOverlapEvents(true);
	Trigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	Trigger->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Trigger->CanCharacterStepUpOn = ECB_No;

	ExitPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ExitPoint"));
	ExitPoint->SetupAttachment(PortalMesh);
	ExitPoint->SetRelativeLocation(FVector(200.0f, 0.0f, 0.0f));
}

void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	Trigger->OnComponentBeginOverlap.AddDynamic(
		this,
		&APortal::OnTriggerBeginOverlap
	);
}

void APortal::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AScaredyImpCharacter* Character = Cast<AScaredyImpCharacter>(OtherActor);

	if (!IsValid(Character) || !IsValid(ExitPoint)) return;

	const bool bTeleported = Character->TeleportTo(
		ExitPoint->GetComponentLocation(),
		ExitPoint->GetComponentRotation()
	);

	if (!bTeleported) return;

	if (UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
	}
}


#include "Pickups/PickupBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/RotatingMovementComponent.h"

APickupBase::APickupBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	SetRootComponent(PickupMesh);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupMesh->SetGenerateOverlapEvents(true);
	PickupMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	PickupMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->SetUpdatedComponent(PickupMesh);
	RotatingMovementComponent->RotationRate = FRotator(0.0f, RotationSpeed, 0.0f);
	RotatingMovementComponent->bRotationInLocalSpace = true;
}

void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	PickupMesh->OnComponentBeginOverlap.AddDynamic(this, &APickupBase::OnPickupBeginOverlap);
}

bool APickupBase::TryPickup(ACharacter* Character)
{
	// Override by inherited class
	return false;
}

void APickupBase::OnPickupBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!IsValid(Character)) return;

	if (TryPickup(Character))
	{
		Destroy();
	}
}


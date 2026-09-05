
#include "Obstacle/SwingingObstacle.h"
#include "Comps/SwingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFrameWork/Character.h"
#include "ScaredyImp.h"

ASwingingObstacle::ASwingingObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	ObstacleSwingComponent = CreateDefaultSubobject<USwingComponent>(TEXT("ObstacleSwingComponent"));

	PushTriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PushTriggerMesh"));
	PushTriggerMesh->SetupAttachment(ObstacleMesh);
	PushTriggerMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PushTriggerMesh->SetGenerateOverlapEvents(true);
	PushTriggerMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	PushTriggerMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PushTriggerMesh->SetVisibility(false);
	PushTriggerMesh->SetCastShadow(false);
	PushTriggerMesh->CanCharacterStepUpOn = ECB_No;
}

void ASwingingObstacle::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(ObstacleMesh) || !IsValid(PushTriggerMesh)) return;

	PushTriggerMesh->SetStaticMesh(ObstacleMesh->GetStaticMesh());
	PushTriggerMesh->SetRelativeTransform(FTransform::Identity);
	PushTriggerMesh->SetRelativeScale3D(FVector(PushTriggerScale));
	PushTriggerMesh->OnComponentBeginOverlap.AddDynamic(this, &ASwingingObstacle::OnPushBoxBeginOverlap);
}

void ASwingingObstacle::OnPushBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!IsValid(Character)) return;

	const FVector CharacterLocation = Character->GetActorLocation();

	FVector ContactPoint = FVector::ZeroVector;

	const float Distance = ObstacleMesh->GetClosestPointOnCollision(
		CharacterLocation,
		ContactPoint
	);

	if (Distance < 0.0f) return;

	FVector PushDirection = CharacterLocation - ContactPoint;

	PushDirection.Z = 0.0f;

	if (PushDirection.IsNearlyZero()) return;

	PushDirection.Normalize();

	const FVector LaunchVelocity = PushDirection * PushStrength;

	Character->LaunchCharacter(
		LaunchVelocity,
		true,  // xy
		false  // z
	);


	UE_LOG(
		LogScaredyImp,
		Warning,
		TEXT("[SwingingObstacle] PushTrigger overlap: %s"),
		*GetNameSafe(OtherActor)
	);
}

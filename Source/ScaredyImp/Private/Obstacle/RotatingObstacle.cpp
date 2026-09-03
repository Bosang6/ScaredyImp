
#include "Obstacle/RotatingObstacle.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "ScaredyImp.h"

ARotatingObstacle::ARotatingObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->SetUpdatedComponent(ObstacleMesh);
	RotatingMovementComponent->RotationRate = FRotator(0.0f, RotationSpeed, 0.0f);
	RotatingMovementComponent->bRotationInLocalSpace = true;

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

void ARotatingObstacle::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValid(ObstacleMesh) || !IsValid(PushTriggerMesh)) return;

	PushTriggerMesh->SetStaticMesh(ObstacleMesh->GetStaticMesh());
	PushTriggerMesh->SetRelativeTransform(FTransform::Identity);
	PushTriggerMesh->SetRelativeScale3D(FVector(PushTriggerScale));
	PushTriggerMesh->OnComponentBeginOverlap.AddDynamic(this, &ARotatingObstacle::OnPushBoxBeginOverlap);
}

void ARotatingObstacle::OnPushBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!IsValid(Character) ||
		!IsValid(ObstacleMesh) ||
		!IsValid(RotatingMovementComponent))
	{
		return;
	}

	const FVector CharacterLocation = Character->GetActorLocation();

	// 1. Find contact point
	FVector ContactPoint = FVector::ZeroVector;

	if (bFromSweep)
	{
		ContactPoint = SweepResult.ImpactPoint;
	}
	else
	{
		const float Distance = ObstacleMesh->GetClosestPointOnCollision(CharacterLocation, ContactPoint);

		if (Distance < 0.0f)
		{
			return;
		}
	}

	// 2. Calculate push direction

	FVector PushDirection = CharacterLocation - ContactPoint;

	// This obstacle should only push the player horizontally.
	PushDirection.Z = 0.0f;

	// Fallback in case the Character center is close to the contact point.
	if (PushDirection.IsNearlyZero())
	{
		PushDirection = CharacterLocation - ObstacleMesh->GetComponentLocation();
		PushDirection.Z = 0.0f;
	}

	if (PushDirection.IsNearlyZero())
	{
		return;
	}

	PushDirection.Normalize();

	// 3. Launch Character

	const FVector LaunchVelocity = PushDirection * PushStrength;

	Character->LaunchCharacter(
		LaunchVelocity,
		true,   // Override XY velocity
		false   // Keep current Z velocity
	);

	UE_LOG(LogScaredyImp, Warning, TEXT("[RotatingObstacle] %s pushed by %s."), *GetNameSafe(Character), *GetNameSafe(OverlappedComponent));
}

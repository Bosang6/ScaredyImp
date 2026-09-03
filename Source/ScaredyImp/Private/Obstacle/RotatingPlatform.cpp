
#include "Obstacle/RotatingPlatform.h"
#include "GameFramework/RotatingMovementComponent.h"

ARotatingPlatform::ARotatingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->SetUpdatedComponent(ObstacleMesh);
	RotatingMovementComponent->RotationRate = FRotator(0.0f, RotationSpeed, 0.0f);
	RotatingMovementComponent->bRotationInLocalSpace = true;
}

void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(RotatingMovementComponent))
	{
		RotatingMovementComponent->RotationRate = FRotator(0.0f, RotationSpeed, 0.0f);
	}

}


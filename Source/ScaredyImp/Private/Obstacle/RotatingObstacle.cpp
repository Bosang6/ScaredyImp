
#include "Obstacle/RotatingObstacle.h"
#include "GameFramework/RotatingMovementComponent.h"

ARotatingObstacle::ARotatingObstacle()
{
	RotatingMovementComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComponent"));
	RotatingMovementComponent->SetUpdatedComponent(ObstacleRoot);
	RotatingMovementComponent->RotationRate = FRotator(0.0f, 90.0f, 0.0f);
	RotatingMovementComponent->bRotationInLocalSpace = true;
}

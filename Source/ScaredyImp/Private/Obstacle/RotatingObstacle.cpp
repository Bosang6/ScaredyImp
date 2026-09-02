
#include "Obstacle/RotatingObstacle.h"
#include "Comps/ObstacleRotationComponent.h"

ARotatingObstacle::ARotatingObstacle()
{
	RotationComponent = CreateDefaultSubobject<UObstacleRotationComponent>(TEXT("RotationComponent"));
}

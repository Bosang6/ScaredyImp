#include "Comps/MoverComponent.h"

#include "Obstacle/MovingObstacle.h"

AMovingObstacle::AMovingObstacle()
{
	MoverComponent = CreateDefaultSubobject<UMoverComponent>(TEXT("MoverComponent"));
}

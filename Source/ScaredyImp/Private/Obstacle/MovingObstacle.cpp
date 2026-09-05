#include "Obstacle/MovingObstacle.h"
#include "Comps/MoverComponent.h"


AMovingObstacle::AMovingObstacle()
{
	MoverComponent = CreateDefaultSubobject<UMoverComponent>(TEXT("MoverComponent"));
}

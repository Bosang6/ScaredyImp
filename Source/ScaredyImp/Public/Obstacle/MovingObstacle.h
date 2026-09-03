
#pragma once

#include "CoreMinimal.h"
#include "Obstacle/ObstacleBase.h"
#include "MovingObstacle.generated.h"

class UMoverComponent;

UCLASS()
class SCAREDYIMP_API AMovingObstacle : public AObstacleBase
{
	GENERATED_BODY()

public:
	AMovingObstacle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obastacle")
	TObjectPtr<UMoverComponent> MoverComponent;
};


#pragma once

#include "CoreMinimal.h"
#include "Obstacle/ObstacleBase.h"
#include "RotatingObstacle.generated.h"

class URotatingMovementComponent;

UCLASS()
class SCAREDYIMP_API ARotatingObstacle : public AObstacleBase
{
	GENERATED_BODY()
	
public:
	ARotatingObstacle();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;
};

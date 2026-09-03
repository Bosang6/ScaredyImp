
#pragma once

#include "CoreMinimal.h"
#include "Obstacle/ObstacleBase.h"
#include "RotatingPlatform.generated.h"

class URotatingMovementComponent;

UCLASS()
class SCAREDYIMP_API ARotatingPlatform : public AObstacleBase
{
	GENERATED_BODY()
	
public:	
	ARotatingPlatform();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
	float RotationSpeed = 90.0f;
};

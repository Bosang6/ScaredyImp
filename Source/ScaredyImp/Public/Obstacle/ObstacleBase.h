
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleBase.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS(Abstract)
class SCAREDYIMP_API AObstacleBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleBase();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obastacle")
	TObjectPtr<USceneComponent> ObstacleRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obastacle")
	TObjectPtr<UStaticMeshComponent> ObstacleMesh;
};

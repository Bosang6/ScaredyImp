
#pragma once

#include "CoreMinimal.h"
#include "Obstacle/ObstacleBase.h"
#include "RotatingObstacle.generated.h"

class URotatingMovementComponent;
class UStaticMeshComponent;

UCLASS()
class SCAREDYIMP_API ARotatingObstacle : public AObstacleBase
{
	GENERATED_BODY()
	
public:
	ARotatingObstacle();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnPushBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TObjectPtr<UStaticMeshComponent> PushTriggerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle", meta = (ClampMin = "1.0"))
	float RotationSpeed = 90.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle", meta = (ClampMin = "1.0"))
	float PushTriggerScale = 1.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle", meta = (ClampMin = "0.0"))
	float PushStrength = 600.0f;
};

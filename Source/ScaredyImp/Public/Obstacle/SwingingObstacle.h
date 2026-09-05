
#pragma once

#include "CoreMinimal.h"
#include "Obstacle/ObstacleBase.h"
#include "SwingingObstacle.generated.h"

class USwingComponent;
class UStaticMeshComponent;

UCLASS()
class SCAREDYIMP_API ASwingingObstacle : public AObstacleBase
{
	GENERATED_BODY()

public:
	ASwingingObstacle();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Swing")
	TObjectPtr<USwingComponent> ObstacleSwingComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TObjectPtr<UStaticMeshComponent> PushTriggerMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle", meta = (ClampMin = "1.0"))
	float PushTriggerScale = 1.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle", meta = (ClampMin = "0.0"))
	float PushStrength = 1200.0f;
};

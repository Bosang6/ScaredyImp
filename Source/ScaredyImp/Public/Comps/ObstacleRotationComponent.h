
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ObstacleRotationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API UObstacleRotationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UObstacleRotationComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	FVector RotationAxis = FVector::UpVector;

	// Rotation speed in degress per second
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation", meta =(ClampMin = "0.0"))
	float RotationSpeed = 90.0f;

private:
	TObjectPtr<AActor> Owner = nullptr;
};

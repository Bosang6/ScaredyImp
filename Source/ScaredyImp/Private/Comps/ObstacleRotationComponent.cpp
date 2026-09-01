
#include "Comps/ObstacleRotationComponent.h"
#include "ScaredyImp.h"

UObstacleRotationComponent::UObstacleRotationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UObstacleRotationComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	if (!IsValid(Owner))
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[ObstacleRotationComponent] Owner invalid."));
	}
}


void UObstacleRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(Owner)) return;

	const FVector NormalizedAxis = RotationAxis.GetSafeNormal();

	const float DeltaAngle = RotationSpeed * DeltaTime;

	const FQuat DeltaRotation(
		NormalizedAxis,
		FMath::DegreesToRadians(DeltaAngle)
	);

	Owner->AddActorLocalRotation(DeltaRotation);
}

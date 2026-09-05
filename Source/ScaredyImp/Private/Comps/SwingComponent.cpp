
#include "Comps/SwingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ScaredyImp.h"

USwingComponent::USwingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USwingComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;
	
	UStaticMeshComponent* TargetMesh = Owner->GetComponentByClass<UStaticMeshComponent>();
	if (!IsValid(TargetMesh)) return;

	SetUpdatedComponent(TargetMesh);

	InitialRotation = UpdatedComponent->GetComponentRotation();
}

void USwingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (ShouldSkipUpdate(DeltaTime)) return;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!IsValid(UpdatedComponent)) return;

	ElapsedTime += DeltaTime;

	const float AngularSpeed = 2.0f * PI / SwingPeriod;
	const float StartPhase = StartAlpha * 2.0f * PI;
	const float Phase = ElapsedTime * AngularSpeed + StartPhase;
	const float SwingAngle = FMath::Sin(Phase) * MaxSwingAngle;

	FRotator NewRotation = InitialRotation;

	switch (SwingAxis)
	{
		case ESwingAxis::Pitch:
			NewRotation.Pitch += SwingAngle;
			break;
		case ESwingAxis::Yaw:
			NewRotation.Yaw += SwingAngle;
			break;
		case ESwingAxis::Roll:
			NewRotation.Roll += SwingAngle;
			break;
	}

	//TargetMesh->SetRelativeRotation(NewRotation);

	const bool bEnableCollision = false;

	MoveUpdatedComponent(
		FVector::ZeroVector,
		NewRotation.Quaternion(),
		bEnableCollision
	);
}



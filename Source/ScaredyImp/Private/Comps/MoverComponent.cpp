
#include "Comps/MoverComponent.h"

UMoverComponent::UMoverComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UMoverComponent::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* Owner = GetOwner();

	if (!IsValid(Owner)) return;

	const FTransform InitialTransform = Owner->GetActorTransform();

	// Convert local start/end to world positions
	WorldStart = InitialTransform.TransformPosition(LocalStart);
	WorldEnd = InitialTransform.TransformPosition(LocalEnd);

	StartAlpha = FMath::Clamp(StartAlpha, 0.0f, 1.0f);
	// Alpha = (sin(Phase) + 1) / 2
	// Phase = asin(Alpha * 2 - 1)
	Phase = FMath::Asin(StartAlpha * 2.0f - 1.0f);

	// Calculate initial position
	const FVector InitialLocation = FMath::Lerp(
		WorldStart,
		WorldEnd,
		StartAlpha
	);

	Owner->SetActorLocation(InitialLocation);
}

void UMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();

	if (!IsValid(Owner)) return;

	Phase += DeltaTime * Speed;
	Phase = FMath::Fmod(Phase, 2.0f * PI);

	const float CurrentAlpha = (FMath::Sin(Phase) + 1.0f) * 0.5f;

	const FVector NewLocation = FMath::Lerp(WorldStart, WorldEnd, CurrentAlpha);

	Owner->SetActorLocation(NewLocation);
}


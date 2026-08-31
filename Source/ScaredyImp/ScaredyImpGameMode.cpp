
#include "ScaredyImpGameMode.h"
#include "Checkpoint/CheckpointSubsystem.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "ScaredyImp.h"

AScaredyImpGameMode::AScaredyImpGameMode()
{
	
}

void AScaredyImpGameMode::BeginPlay()
{
	Super::BeginPlay();

	// There is only one PlayerStart on the map.
	AActor* PlayerStartActor = UGameplayStatics::GetActorOfClass(
		this,
		APlayerStart::StaticClass()
	);

	if (!IsValid(PlayerStartActor))
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[GameMode] PlayerStart not found."));
		return;
	}

	UCheckpointSubsystem* CheckpointSubsystem = GetWorld()->GetSubsystem<UCheckpointSubsystem>();

	if (!IsValid(CheckpointSubsystem))
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[GameMode] CheckpointSubsystem not found."));
		return;
	}

	CheckpointSubsystem->SetLevelStart(PlayerStartActor->GetActorTransform());
}

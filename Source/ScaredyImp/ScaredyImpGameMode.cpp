
#include "ScaredyImpGameMode.h"
#include "Checkpoint/CheckpointSubsystem.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "ScaredyImp.h"

AScaredyImpGameMode::AScaredyImpGameMode()
{
	
}

void AScaredyImpGameMode::RespawnPlayerAtLevelStart(AController* Controller)
{
	if (!IsValid(Controller)) return;

	UCheckpointSubsystem* CheckpointSubsystem = GetWorld()->GetSubsystem<UCheckpointSubsystem>();

	if (!IsValid(CheckpointSubsystem)) return;

	if (CheckpointSubsystem->HasLevelStart())
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[GameMode] Cannot respawn: Level Start is not registered."));
		return;
	}

	const FTransform LevelStartTransform = CheckpointSubsystem->GetLevelStartTransform();

	// Full death means all checkpoint progress of this life is lost.
	CheckpointSubsystem->ResetCheckpoint();
	// Destory Pawn
	APawn* OldPawn = Controller->GetPawn();
	if (IsValid(OldPawn))
	{
		Controller->UnPossess();
		OldPawn->Destroy();
	}
	// GameMode will use the currently configured Default Pawn Class and create a new Pawn at the specified Transform.
	RestartPlayerAtTransform(Controller, LevelStartTransform);
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

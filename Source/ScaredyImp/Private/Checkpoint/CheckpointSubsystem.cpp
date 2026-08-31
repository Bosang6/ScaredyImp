
#include "Checkpoint/CheckpointSubsystem.h"
#include "ScaredyImp.h"

FTransform UCheckpointSubsystem::GetRecoveryTransform() const
{
	if (bHasActiveCheckpoint)
	{
		return CurrentCheckpoint.RespawnTransform;
	}

	return LevelStartTransform;
}

void UCheckpointSubsystem::SetLevelStart(const FTransform& Transform)
{
	LevelStartTransform = Transform;
	bHasLevelStart = true;

	UE_LOG(
		LogScaredyImp, 
		Warning, 
		TEXT("[CheckpointSubsystem] Level Start registered: %s"),
		*LevelStartTransform.GetLocation().ToString()
	);
}

bool UCheckpointSubsystem::HasLevelStart() const
{
	return bHasLevelStart;
}

const FTransform& UCheckpointSubsystem::GetLevelStartTransform() const
{
	return LevelStartTransform;
}

void UCheckpointSubsystem::ActivateCheckpoint(const FCheckpointData& CheckpointData)
{
	CurrentCheckpoint = CheckpointData;
	bHasActiveCheckpoint = true;
}

void UCheckpointSubsystem::ResetCheckpoint()
{
	CurrentCheckpoint = FCheckpointData();
	bHasActiveCheckpoint = false;
}

bool UCheckpointSubsystem::HasActiveCheckpoint() const
{
	return bHasActiveCheckpoint;
}

const FCheckpointData& UCheckpointSubsystem::GetCurrentCheckpoint() const
{
	return CurrentCheckpoint;
}

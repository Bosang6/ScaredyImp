
#include "Checkpoint/CheckpointSubsystem.h"
#include "ScaredyImp.h"

FTransform UCheckpointSubsystem::GetRecoveryTransform() const
{
	if (bHasActiveCheckpoint)
	{
		return CurrentCheckpoint;
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

void UCheckpointSubsystem::ActivateCheckpoint(const FTransform& RespawnTransform)
{
	const bool bCheckpointChanged = !bHasActiveCheckpoint || !CurrentCheckpoint.Equals(RespawnTransform);

	CurrentCheckpoint = RespawnTransform;
	bHasActiveCheckpoint = true;

	if (bCheckpointChanged)
	{
		bHasSavedCurrentCheckpoint = false;
	}
}

void UCheckpointSubsystem::ResetCheckpoint()
{
	CurrentCheckpoint = FTransform::Identity;
	bHasActiveCheckpoint = false;

	bHasSavedCurrentCheckpoint = false;
}

bool UCheckpointSubsystem::HasActiveCheckpoint() const
{
	return bHasActiveCheckpoint;
}

const FTransform& UCheckpointSubsystem::GetCurrentCheckpoint() const
{
	return CurrentCheckpoint;
}

bool UCheckpointSubsystem::HasSavedCurrentCheckpoint() const
{
	return bHasSavedCurrentCheckpoint;
}

void UCheckpointSubsystem::MarkCurrentCheckpointSaved()
{
	bHasSavedCurrentCheckpoint = true;
}


#include "Checkpoint/CheckpointSubsystem.h"

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


#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Checkpoint/CheckpointTypes.h"
#include "CheckpointSubsystem.generated.h"

UCLASS()
class SCAREDYIMP_API UCheckpointSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void ActivateCheckpoint(const FCheckpointData& CheckpointData);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void ResetCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	bool HasActiveCheckpoint() const;

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	const FCheckpointData& GetCurrentCheckpoint() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
	FCheckpointData CurrentCheckpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
	bool bHasActiveCheckpoint = false;
};

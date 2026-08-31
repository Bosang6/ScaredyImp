
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
	FTransform GetRecoveryTransform() const;

	// Level Start
	UFUNCTION(BlueprintCallable, Category = "Level Start")
	void SetLevelStart(const FTransform& Transform);

	UFUNCTION(BlueprintCallable, Category = "Level Start")
	bool HasLevelStart() const;

	UFUNCTION(BlueprintCallable, Category = "Level Start")
	const FTransform& GetLevelStartTransform() const;

	// Checkpoint
	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void ActivateCheckpoint(const FCheckpointData& CheckpointData);

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	void ResetCheckpoint();

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	bool HasActiveCheckpoint() const;

	UFUNCTION(BlueprintCallable, Category = "Checkpoint")
	const FCheckpointData& GetCurrentCheckpoint() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Start", meta = (AllowPrivateAccess = "true"))
	FTransform LevelStartTransform = FTransform::Identity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level Start", meta = (AllowPrivateAccess = "true"))
	bool bHasLevelStart = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
	FCheckpointData CurrentCheckpoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint", meta = (AllowPrivateAccess = "true"))
	bool bHasActiveCheckpoint = false;
};

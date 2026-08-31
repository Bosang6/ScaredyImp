
#pragma once

#include "CoreMinimal.h"

#include "CheckpointTypes.generated.h"

USTRUCT(BlueprintType)
struct FCheckpointData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Checkpoint")
	FName CheckPointID = NAME_None;

	UPROPERTY(BlueprintReadOnly, Category = "Checkpoint")
	FTransform RespawnTransform = FTransform::Identity;
	
};


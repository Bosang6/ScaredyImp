
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ScaredyImpSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FScaredyImpPlayerSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Player")
	int32 Health = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Player")
	int32 Coins = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Checkpoint")
	FTransform CheckpointTransform = FTransform::Identity;
};

UCLASS()
class SCAREDYIMP_API UScaredyImpSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = "Save")
	FScaredyImpPlayerSaveData PlayerData;
};

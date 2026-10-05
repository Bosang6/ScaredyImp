
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScaredyImpGameFlowConfig.generated.h"

class UWorld;

UCLASS(BlueprintType)
class SCAREDYIMP_API UScaredyImpGameFlowConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> GameplayLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Levels")
	TSoftObjectPtr<UWorld> MainMenuLevel;
};

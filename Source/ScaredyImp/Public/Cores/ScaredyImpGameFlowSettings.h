
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ScaredyImpGameFlowSettings.generated.h"

class UScaredyImpGameFlowConfig;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "ScaredyImp Game Flow"))
class SCAREDYIMP_API UScaredyImpGameFlowSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "Game Flow")
	TSoftObjectPtr<UScaredyImpGameFlowConfig> GameFlowConfig;
};

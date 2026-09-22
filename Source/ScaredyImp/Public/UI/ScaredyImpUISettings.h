
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ScaredyImpUISettings.generated.h"

class UScaredyImpUIConfig;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "ScaredyImp UI"))
class SCAREDYIMP_API UScaredyImpUISettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "UI")
	TSoftObjectPtr<UScaredyImpUIConfig> UIConfig;
};

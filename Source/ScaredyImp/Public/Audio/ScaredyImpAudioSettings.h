
#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ScaredyImpAudioSettings.generated.h"

class UScaredyImpAudioConfig;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Scaredy Imp Audio"))
class SCAREDYIMP_API UScaredyImpAudioSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Audio")
	TSoftObjectPtr<UScaredyImpAudioConfig> AudioConfig;
};


#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "ScaredyImpAudioConfig.generated.h"

class USoundBase;

USTRUCT(BlueprintType)
struct FScaredyImpSFXData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USoundBase> Sound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float VolumeMultiplier = 1.0f;
};


UCLASS()
class SCAREDYIMP_API UScaredyImpAudioConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, TObjectPtr<USoundBase>> MusicMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag, FScaredyImpSFXData> SFXMap;
};

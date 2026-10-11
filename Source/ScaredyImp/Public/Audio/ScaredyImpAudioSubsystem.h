
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "ScaredyImpAudioSubsystem.generated.h"

class UScaredyImpAudioConfig;

UCLASS()
class SCAREDYIMP_API UScaredyImpAudioSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void PlaySFX2D(const FGameplayTag& SFXTag);

private:
	UPROPERTY()
	TObjectPtr<UScaredyImpAudioConfig> AudioConfig;
};

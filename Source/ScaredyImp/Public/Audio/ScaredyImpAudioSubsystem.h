
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

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetMusicVolume(float Volume);
	UFUNCTION(BlueprintCallable, Category = "Audio")
	void SetSFXVolume(float Volume);

	void PlaySFX2D(const FGameplayTag& SFXTag);

private:
	UPROPERTY()
	TObjectPtr<UScaredyImpAudioConfig> AudioConfig;

	float MusicVolumeMultiplier = 1.0f;
	float SFXVolumeMultiplier = 1.0f;
};

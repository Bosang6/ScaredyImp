
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "ScaredyImpAudioSubsystem.generated.h"

class UScaredyImpAudioConfig;
class UAudioComponent;

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

	UFUNCTION(BlueprintCallable, Category = "Audio")
	float GetMusicVolume() const { return MusicVolumeMultiplier; }

	UFUNCTION(BlueprintCallable, Category = "Audio")
	float GetSFXVolume() const { return SFXVolumeMultiplier; }

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlaySFX2D(const FGameplayTag& SFXTag);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void PlayMusic(const FGameplayTag& MusicTag);

	UFUNCTION(BlueprintCallable, Category = "Audio")
	void StopMusic();

private:
	UPROPERTY()
	TObjectPtr<UScaredyImpAudioConfig> AudioConfig;

	UPROPERTY()
	TObjectPtr<UAudioComponent> MusicAudioComponent;

	FGameplayTag CurrentMusicTag;

	float MusicVolumeMultiplier = 1.0f;
	float SFXVolumeMultiplier = 1.0f;
};

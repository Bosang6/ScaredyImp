

#include "Audio/ScaredyImpAudioSubsystem.h"
#include "Audio/ScaredyImpAudioConfig.h"
#include "Audio/ScaredyImpAudioSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"


void UScaredyImpAudioSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UScaredyImpAudioSettings* AudioSettings = GetDefault<UScaredyImpAudioSettings>();
	if (!IsValid(AudioSettings)) return;

	AudioConfig = AudioSettings->AudioConfig.LoadSynchronous();
	if (!IsValid(AudioConfig))
	{
		UE_LOG(LogTemp, Warning, TEXT("AudioSubsystem: Failed to load AudioConfig"));
	}
}

void UScaredyImpAudioSubsystem::Deinitialize()
{
	AudioConfig = nullptr;

	Super::Deinitialize();
}

void UScaredyImpAudioSubsystem::SetMusicVolume(float Volume)
{
	MusicVolumeMultiplier = FMath::Clamp(Volume, 0.0f, 1.0f);

	if (IsValid(MusicAudioComponent))
	{
		MusicAudioComponent->SetVolumeMultiplier(MusicVolumeMultiplier);
	}
}

void UScaredyImpAudioSubsystem::SetSFXVolume(float Volume)
{
	SFXVolumeMultiplier = FMath::Clamp(Volume, 0.0f, 1.0f);
}

void UScaredyImpAudioSubsystem::PlaySFX2D(const FGameplayTag& SFXTag)
{
	if (!IsValid(AudioConfig)) return;

	const TObjectPtr<USoundBase>* Sound = AudioConfig->SFXMap.Find(SFXTag);
	if (!Sound || !IsValid(Sound->Get())) return;

	UGameplayStatics::PlaySound2D(
		GetGameInstance(),
		Sound->Get(),
		SFXVolumeMultiplier
	);
}

void UScaredyImpAudioSubsystem::PlayMusic(const FGameplayTag& MusicTag)
{
	if (!IsValid(AudioConfig)) return;

	const TObjectPtr<USoundBase>* Music = AudioConfig->MusicMap.Find(MusicTag);
	if (!Music || !IsValid(Music->Get())) return;

	// Stop previous music
	if (IsValid(MusicAudioComponent))
	{
		MusicAudioComponent->Stop();
		MusicAudioComponent = nullptr;
	}

	MusicAudioComponent = UGameplayStatics::SpawnSound2D(
		GetGameInstance(),
		Music->Get(),
		MusicVolumeMultiplier,
		1.0f,
		0.0f,
		nullptr,
		true,   // Persist across level transition
		false   // Auto Destroy
	);

	if (IsValid(MusicAudioComponent))
	{
		CurrentMusicTag = MusicTag;
	}
}

void UScaredyImpAudioSubsystem::StopMusic()
{
	if (IsValid(MusicAudioComponent))
	{
		MusicAudioComponent->Stop();
		MusicAudioComponent = nullptr;
	}

	CurrentMusicTag = FGameplayTag();
}



#include "Audio/ScaredyImpAudioSubsystem.h"
#include "Audio/ScaredyImpAudioConfig.h"
#include "Audio/ScaredyImpAudioSettings.h"
#include "Kismet/GameplayStatics.h"


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

void UScaredyImpAudioSubsystem::PlaySFX2D(const FGameplayTag& SFXTag)
{
	if (!IsValid(AudioConfig)) return;

	const FScaredyImpSFXData* SFXData = AudioConfig->SFXMap.Find(SFXTag);
	if (!SFXData || !IsValid(SFXData->Sound)) return;

	UGameplayStatics::PlaySound2D(
		GetGameInstance(),
		SFXData->Sound,
		SFXData->VolumeMultiplier
	);
}

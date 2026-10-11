

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

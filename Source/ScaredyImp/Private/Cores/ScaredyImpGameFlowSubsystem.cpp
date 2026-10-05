
#include "Cores/ScaredyImpGameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Utilities/ScaredyImpFunctionLibrary.h"
#include "Cores/ScaredyImpGameFlowSettings.h"
#include "Cores/ScaredyImpGameFlowConfig.h"

bool UScaredyImpGameFlowSubsystem::StartNewGame()
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return false;

	// Delete previous save
	if (!SaveSubsystem->DeleteSaveGame()) return false;

	return OpenGameplayLevel();
}

bool UScaredyImpGameFlowSubsystem::ContinueGame()
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return false;

	// Load current save from disk
	if (!SaveSubsystem->LoadSaveGame()) return false;

	return OpenGameplayLevel();
}

bool UScaredyImpGameFlowSubsystem::OpenGameplayLevel()
{
	const UScaredyImpGameFlowConfig* Config = GetGameFlowConfig();
	if (!IsValid(Config)) return false;

	if (Config->GameplayLevel.IsNull()) return false;

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Config->GameplayLevel);

	return true;
}

const UScaredyImpGameFlowConfig* UScaredyImpGameFlowSubsystem::GetGameFlowConfig() const
{
	const UScaredyImpGameFlowSettings* Settings = GetDefault<UScaredyImpGameFlowSettings>();
	if (!IsValid(Settings)) return nullptr;

	if (Settings->GameFlowConfig.IsNull()) return nullptr;

	return Settings->GameFlowConfig.LoadSynchronous();
}

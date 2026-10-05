
#include "Cores/ScaredyImpGameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Utilities/ScaredyImpFunctionLibrary.h"

bool UScaredyImpGameFlowSubsystem::StartNewGame(const TSoftObjectPtr<UWorld>& GameplayLevel)
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return false;

	// Delete previous save
	if (!SaveSubsystem->DeleteSaveGame()) return false;

	return OpenGameplayLevel(GameplayLevel);
}

bool UScaredyImpGameFlowSubsystem::ContinueGame(const TSoftObjectPtr<UWorld>& GameplayLevel)
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return false;

	// Load current save from disk
	if (!SaveSubsystem->LoadSaveGame()) return false;

	return OpenGameplayLevel(GameplayLevel);
}

bool UScaredyImpGameFlowSubsystem::OpenGameplayLevel(const TSoftObjectPtr<UWorld>& GameplayLevel)
{
	if (GameplayLevel.IsNull()) return false;

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, GameplayLevel);

	return true;
}

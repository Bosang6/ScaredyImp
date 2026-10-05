
#include "Cores/ScaredyImpGameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Utilities/ScaredyImpFunctionLibrary.h"
#include "Cores/ScaredyImpGameFlowSettings.h"
#include "Cores/ScaredyImpGameFlowConfig.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/ScaredyImpUISubsystem.h"
#include "UI/PopupWidget.h"

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

bool UScaredyImpGameFlowSubsystem::ReturnToMainMenu()
{
	return OpenMainMenu();
}

bool UScaredyImpGameFlowSubsystem::CompleteGame(APlayerController* PlayerController)
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return false;

	// Delete Save Game
	if (!SaveSubsystem->DeleteSaveGame()) return false;

	// Show Victory Popup
	UScaredyImpUISubsystem* UISubsystem = UScaredyImpFunctionLibrary::GetUISubsystem(PlayerController);
	if (!IsValid(UISubsystem)) return false;

	UISubsystem->ShowPopup(EPopupType::Victory);

	return true;
}

void UScaredyImpGameFlowSubsystem::QuitGame()
{
	UGameInstance* GameInstance = GetGameInstance();
	if (!IsValid(GameInstance)) return;

	UWorld* World = GameInstance->GetWorld();
	if (!IsValid(World)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!IsValid(PlayerController)) return;

	UKismetSystemLibrary::QuitGame(
		World,
		PlayerController,
		EQuitPreference::Quit,
		false
	);
}

bool UScaredyImpGameFlowSubsystem::OpenGameplayLevel()
{
	const UScaredyImpGameFlowConfig* Config = GetGameFlowConfig();
	if (!IsValid(Config)) return false;

	if (Config->GameplayLevel.IsNull()) return false;

	return OpenLevel(Config->GameplayLevel);
}

bool UScaredyImpGameFlowSubsystem::OpenMainMenu()
{
	const UScaredyImpGameFlowConfig* Config = GetGameFlowConfig();
	if (!IsValid(Config)) return false;

	if (Config->MainMenuLevel.IsNull()) return false;

	return OpenLevel(Config->MainMenuLevel);
}

bool UScaredyImpGameFlowSubsystem::OpenLevel(const TSoftObjectPtr<UWorld>& Level)
{
	if (Level.IsNull()) return false;

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Level);

	return true;
}

const UScaredyImpGameFlowConfig* UScaredyImpGameFlowSubsystem::GetGameFlowConfig() const
{
	const UScaredyImpGameFlowSettings* Settings = GetDefault<UScaredyImpGameFlowSettings>();
	if (!IsValid(Settings)) return nullptr;

	if (Settings->GameFlowConfig.IsNull()) return nullptr;

	return Settings->GameFlowConfig.LoadSynchronous();
}

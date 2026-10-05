
#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Engine/LocalPlayer.h"
#include "UI/ScaredyImpUISubsystem.h"
#include "UI/PopupWidget.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Cores/ScaredyImpGameFlowSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Utilities/ScaredyImpFunctionLibrary.h"

void UMainMenuWidget::SetContinueBtnEnabled(bool bEnabled)
{
	if (!IsValid(ContinueButton)) return;

	ContinueButton->SetIsEnabled(bEnabled);
}

void UMainMenuWidget::RefreshContinueButtonState()
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem))
	{
		SetContinueBtnEnabled(false);
		return;
	}

	SetContinueBtnEnabled(SaveSubsystem->HasSaveGame());
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(NewGameButton))
	{
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnNewGameClicked);
	}

	if (IsValid(ContinueButton))
	{
		ContinueButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnContinueButtonClicked);
	}

	if (IsValid(SettingsButton))
	{
		SettingsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	}

	if (IsValid(QuitButton))
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
	}

	RefreshContinueButtonState();
}

void UMainMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(NewGameButton))
	{
		NewGameButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::OnNewGameClicked);
	}

	if (IsValid(ContinueButton))
	{
		ContinueButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::OnContinueButtonClicked);
	}

	if (IsValid(SettingsButton))
	{
		SettingsButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	}

	if (IsValid(QuitButton))
	{
		QuitButton->OnClicked.RemoveDynamic(this, &UMainMenuWidget::OnQuitButtonClicked);
	}
}

void UMainMenuWidget::OnNewGameClicked_Implementation()
{
	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return;

	// If not exist a game save, start immediately
	if (!SaveSubsystem->HasSaveGame())
	{
		UScaredyImpGameFlowSubsystem* GameFlowSubsystem = UScaredyImpFunctionLibrary::GetGameFlowSubsystem(this);
		if (!IsValid(GameFlowSubsystem)) return;

		GameFlowSubsystem->StartNewGame();
		return;
	}

	// Ask player for confirmation
	APlayerController* PlayerController = GetOwningPlayer();
	if (!IsValid(PlayerController)) return;

	UScaredyImpUISubsystem* UISubsystem = UScaredyImpFunctionLibrary::GetUISubsystem(PlayerController);
	if (!IsValid(UISubsystem)) return;

	UISubsystem->ShowPopup(EPopupType::ConfirmNewGame);
}

void UMainMenuWidget::OnContinueButtonClicked_Implementation()
{
	UScaredyImpGameFlowSubsystem* GameFlowSubsystem = UScaredyImpFunctionLibrary::GetGameFlowSubsystem(this);
	if (!IsValid(GameFlowSubsystem)) return;

	if (!GameFlowSubsystem->ContinueGame())
	{
		RefreshContinueButtonState();
	}
}

void UMainMenuWidget::OnSettingsButtonClicked_Implementation()
{
}

void UMainMenuWidget::OnQuitButtonClicked_Implementation()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (!IsValid(PlayerController)) return;

	UScaredyImpUISubsystem* UISubsystem = ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(PlayerController);

	if (!IsValid(UISubsystem)) return;

	UISubsystem->ShowPopup(EPopupType::ConfirmQuit);
}

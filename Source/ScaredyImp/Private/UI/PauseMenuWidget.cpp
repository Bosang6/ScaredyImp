
#include "UI/PauseMenuWidget.h"
#include "Components/Button.h"
#include "Engine/LocalPlayer.h"
#include "UI/ScaredyImpUISubsystem.h"

void UPauseMenuWidget::NativeConstruct()
{
	if (IsValid(ResumeButton))
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnResumeButtonClicked);
	}

	if (IsValid(SettingsButton))
	{
		SettingsButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnSettingsButtonClicked);
	}

	if (IsValid(MainMenuButton))
	{
		MainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::OnSettingsButtonClicked);
	}
}

void UPauseMenuWidget::NativeDestruct()
{
	if (IsValid(ResumeButton))
	{
		ResumeButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::OnResumeButtonClicked);
	}

	if (IsValid(SettingsButton))
	{
		SettingsButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::OnSettingsButtonClicked);
	}

	if (IsValid(MainMenuButton))
	{
		MainMenuButton->OnClicked.RemoveDynamic(this, &UPauseMenuWidget::OnMainMenuButtonClicked);
	}
}

void UPauseMenuWidget::OnResumeButtonClicked_Implementation()
{
	APlayerController* PlayerController = GetOwningPlayer();
	if (!IsValid(PlayerController)) return;

	UScaredyImpUISubsystem* UISubsystem = ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(PlayerController);
	if (!IsValid(UISubsystem)) return;

	UISubsystem->HidePauseMenu();
}

void UPauseMenuWidget::OnSettingsButtonClicked_Implementation()
{
}

void UPauseMenuWidget::OnMainMenuButtonClicked_Implementation()
{
}

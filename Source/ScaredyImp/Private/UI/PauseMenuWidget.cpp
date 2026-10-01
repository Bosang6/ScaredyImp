
#include "UI/PauseMenuWidget.h"
#include "Components/Button.h"

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
}

void UPauseMenuWidget::OnSettingsButtonClicked_Implementation()
{
}

void UPauseMenuWidget::OnMainMenuButtonClicked_Implementation()
{
}

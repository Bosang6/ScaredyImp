
#include "UI/MainMenuWidget.h"
#include "Components/Button.h"

void UMainMenuWidget::SetContienueBtnEnabled(bool bEnabled)
{
	if (!IsValid(ContinueButton)) return;

	ContinueButton->SetIsEnabled(bEnabled);
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
}

void UMainMenuWidget::OnContinueButtonClicked_Implementation()
{
}

void UMainMenuWidget::OnSettingsButtonClicked_Implementation()
{
}

void UMainMenuWidget::OnQuitButtonClicked_Implementation()
{
}


#include "UI/PopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UPopupWidget::SetupPopup(const FText& InTitle, const FText& InContent, const FText& InConfirmeText, const FText& InCancelText)
{
	if (IsValid(TitleText))
	{
		TitleText->SetText(InTitle);
	}

	if (IsValid(ContentText))
	{
		ContentText->SetText(InContent);
	}

	if (IsValid(ConfirmText))
	{
		ConfirmText->SetText(InConfirmeText);
	}

	if (IsValid(CancelText))
	{
		CancelText->SetText(InCancelText);
	}
}

void UPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ConfirmButton))
	{
		ConfirmButton->OnClicked.AddUniqueDynamic(this, &UPopupWidget::OnConfirmClicked);
	}

	if (IsValid(CancelButton))
	{
		CancelButton->OnClicked.AddUniqueDynamic(this, &UPopupWidget::OnCancelClicked);
	}
}

void UPopupWidget::NativeDestruct()
{
	if (IsValid(ConfirmButton))
	{
		ConfirmButton->OnClicked.RemoveDynamic(this, &UPopupWidget::OnConfirmClicked);
	}

	if (IsValid(CancelButton))
	{
		CancelButton->OnClicked.RemoveDynamic(this, &UPopupWidget::OnCancelClicked);
	}

	Super::NativeDestruct();
}

void UPopupWidget::OnConfirmClicked()
{
	OnPopupResult.Broadcast(true);
}

void UPopupWidget::OnCancelClicked()
{
	OnPopupResult.Broadcast(false);
}

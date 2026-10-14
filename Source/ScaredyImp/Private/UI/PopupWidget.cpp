
#include "UI/PopupWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI/ScaredyImpUISubsystem.h"
#include "Engine/LocalPlayer.h"
#include "Audio/ScaredyImpAudioSubsystem.h"
#include "Audio/ScaredyImpAudioGameplayTags.h"

void UPopupWidget::SetupPopup(const FText& InTitle, const FText& InContent, const FText& InConfirmText, const FText& InCancelText)
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
		ConfirmText->SetText(InConfirmText);
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
		ConfirmButton->OnClicked.AddDynamic(this, &UPopupWidget::OnConfirmClicked);
		ConfirmButton->OnHovered.AddDynamic(this, &UPopupWidget::OnButtonHovered);
		ConfirmButton->OnClicked.AddDynamic(this, &UPopupWidget::OnButtonClicked);
	}

	if (IsValid(CancelButton))
	{
		CancelButton->OnClicked.AddDynamic(this, &UPopupWidget::OnCancelClicked);
		CancelButton->OnHovered.AddDynamic(this, &UPopupWidget::OnButtonHovered);
		CancelButton->OnClicked.AddDynamic(this, &UPopupWidget::OnButtonClicked);
	}
}

void UPopupWidget::NativeDestruct()
{
	if (IsValid(ConfirmButton))
	{
		ConfirmButton->OnClicked.RemoveDynamic(this, &UPopupWidget::OnConfirmClicked);
		ConfirmButton->OnHovered.RemoveDynamic(this, &UPopupWidget::OnButtonHovered);
		ConfirmButton->OnClicked.RemoveDynamic(this, &UPopupWidget::OnButtonClicked);
	}

	if (IsValid(CancelButton))
	{
		CancelButton->OnClicked.RemoveDynamic(this, &UPopupWidget::OnCancelClicked);
		CancelButton->OnHovered.RemoveDynamic(this, &UPopupWidget::OnButtonHovered);
		CancelButton->OnClicked.RemoveDynamic(this, &UPopupWidget::OnButtonClicked);
	}

	Super::NativeDestruct();
}

void UPopupWidget::OnButtonHovered()
{
	if (UScaredyImpAudioSubsystem* AudioSubsystem = GetGameInstance()->GetSubsystem<UScaredyImpAudioSubsystem>())
	{
		AudioSubsystem->PlaySFX2D(ScaredyImpAudioGameplayTags::Audio_SFX_UI_Hover);
	}
}

void UPopupWidget::OnButtonClicked()
{
	if (UScaredyImpAudioSubsystem* AudioSubsystem = GetGameInstance()->GetSubsystem<UScaredyImpAudioSubsystem>())
	{
		AudioSubsystem->PlaySFX2D(ScaredyImpAudioGameplayTags::Audio_SFX_UI_Clicked);
	}
}

void UPopupWidget::OnConfirmClicked_Implementation()
{
}

void UPopupWidget::OnCancelClicked_Implementation()
{
}

void UPopupWidget::RequestClosePopup()
{
	APlayerController* PlayerController = GetOwningPlayer();

	if (!IsValid(PlayerController)) return;

	if (UScaredyImpUISubsystem* UISubsystem = ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(PlayerController))
	{
		UISubsystem->ClosePopup();
	}
}

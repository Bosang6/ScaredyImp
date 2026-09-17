
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPopupResult, bool, bConfirmed);

UCLASS()
class SCAREDYIMP_API UPopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupPopup(
		const FText& InTitle,
		const FText& InContext,
		const FText& InConfirmeText,
		const FText& InCancelText
	);

	UPROPERTY(BlueprintAssignable, Category = "Popup")
	FOnPopupResult OnPopupResult;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnConfirmClicked();

	UFUNCTION()
	void OnCancelClicked();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TitleText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ContentText;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ConfirmText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CancelText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ConfirmButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CancelButton;
};

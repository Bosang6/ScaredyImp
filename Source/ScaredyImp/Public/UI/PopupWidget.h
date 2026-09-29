
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopupWidget.generated.h"

class UTextBlock;
class UButton;

UENUM(BlueprintType)
enum class EPopupType : uint8
{
	GameOver,
	Victory,
	ConfirmNewGame,
	ConfirmQuit
};

UCLASS()
class SCAREDYIMP_API UPopupWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Popup")
	void SetupPopup(
		const FText& InTitle,
		const FText& InContent,
		const FText& InConfirmText,
		const FText& InCancelText
	);

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Popup")
	void OnConfirmClicked();
	virtual void OnConfirmClicked_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Popup")
	void OnCancelClicked();
	virtual void OnCancelClicked_Implementation();

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

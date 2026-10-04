
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;

UCLASS()
class SCAREDYIMP_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetContinueBtnEnabled(bool bEnabled);
	void RefreshContinueButtonState();

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Main Menu")
	void OnNewGameClicked();
	virtual void OnNewGameClicked_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Main Menu")
	void OnContinueButtonClicked();
	virtual void OnContinueButtonClicked_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Main Menu")
	void OnSettingsButtonClicked();
	virtual void OnSettingsButtonClicked_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Main Menu")
	void OnQuitButtonClicked();
	virtual void OnQuitButtonClicked_Implementation();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ContinueButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu")
	TSoftObjectPtr<UWorld> GameplayLevel;
};

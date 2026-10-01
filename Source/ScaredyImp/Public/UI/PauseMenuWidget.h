
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UButton;

UCLASS()
class SCAREDYIMP_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Pause Menu")
	void OnResumeButtonClicked();
	virtual void OnResumeButtonClicked_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Pause Menu")
	void OnSettingsButtonClicked();
	virtual void OnSettingsButtonClicked_Implementation();

	UFUNCTION(BlueprintNativeEvent, Category = "Pause Menu")
	void OnMainMenuButtonClicked();
	virtual void OnMainMenuButtonClicked_Implementation();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ResumeButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> SettingsButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MainMenuButton;
};


#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScaredyImpUIConfig.generated.h"

class UUserWidget;
class UHUDWidget;
class UPopupWidget;
class UMainMenuWidget;
class UPauseMenuWidget;
enum class EPopupType : uint8;

UCLASS()
class SCAREDYIMP_API UScaredyImpUIConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|MainMenu")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|HUD")
	TSubclassOf<UHUDWidget> GameplayHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Pause")
	TSubclassOf<UPauseMenuWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Popup")
	TMap<EPopupType, TSubclassOf<UPopupWidget>> PopupWidgetClasses;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Notification")
	TSubclassOf<UUserWidget> AutoSaveWidgetClass;
};

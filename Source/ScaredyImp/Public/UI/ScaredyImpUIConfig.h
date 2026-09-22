
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ScaredyImpUIConfig.generated.h"

class UUserWidget;

UCLASS()
class SCAREDYIMP_API UScaredyImpUIConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|MainMenu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|HUD")
	TSubclassOf<UUserWidget> GameplayHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Pause")
	TSubclassOf<UUserWidget> PauseMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|Popup")
	TSubclassOf<UUserWidget> PopupWidgetClass;
};

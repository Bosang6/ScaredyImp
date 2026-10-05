
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScaredyImpUISubsystem.generated.h"

class UScaredyImpUIConfig;
class UHUDWidget;
class UMainMenuWidget;
class UPauseMenuWidget;
class AEnemyBase;
class APawn;
class UPopupWidget;
class AScaredyImpCharacter;
class UUserWidget;
enum class EPopupType : uint8;

UENUM()
enum class EScaredyImpUIContext : uint8
{
	None,
	MainMenu,
	Gameplay
};

UCLASS()
class SCAREDYIMP_API UScaredyImpUISubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& CollectionBase) override;
	virtual void Deinitialize() override;

	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;
	
	APlayerController* GetOwningPlayerController() const;

	void SetUIContext(EScaredyImpUIContext NewContext);

	EScaredyImpUIContext GetUIContext() const { return CurrentUIContext; }

	void ShowMainMenu();
	void HideMainMenu();

	void ShowPauseMenu();
	void HidePauseMenu();

	void ShowGameplayHUD();
	void HideGameplayHUD();

	void ShowBossStatus(AEnemyBase* Boss);
	void HideBossStatus();

	UFUNCTION(BlueprintCallable, Category = "UI|Popup")
	UPopupWidget* ShowPopup(EPopupType PopupType);
	UFUNCTION(BlueprintCallable, Category = "UI|Popup")
	void ClosePopup();

	void ShowAutoSaveWidget();
	void HideAutoSaveWidget();

	UFUNCTION()
	void OnPlayerDeath();

	void OnGameSaved();

private:
	void EnterUIContext(EScaredyImpUIContext Context);
	void ExitUIContext(EScaredyImpUIContext Context);

	void ClearRuntimeUI();
	void RebuildCurrentUI();

	void UpdatePlayerControllerBinding(APlayerController* NewPlayerController);
	void BindToPlayerController(APlayerController* PlayerController);
	void UnbindFromPlayerController();

	void BindToCharacter(AScaredyImpCharacter* Character);
	void UnbindFromCharacter(AScaredyImpCharacter* Character);

	void SetUIInputMode(UUserWidget* WidgetToFocus = nullptr);
	void RestoreGameInputMode();

	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

private:
	EScaredyImpUIContext CurrentUIContext = EScaredyImpUIContext::None;

	UPROPERTY(Transient)
	TObjectPtr<UScaredyImpUIConfig> UIConfig;

	UPROPERTY(Transient)
	TObjectPtr<UMainMenuWidget> MainMenuWidget;

	UPROPERTY(Transient)
	TObjectPtr<UPauseMenuWidget> PauseMenuWidget;

	UPROPERTY(Transient)
	TObjectPtr<UHUDWidget> GameplayHUDWidget;

	UPROPERTY(Transient)
	TObjectPtr<UPopupWidget> ActivePopupWidget;

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> AutoSaveWidget;

	FTimerHandle AutoSaveWidgetTimerHandle;

	TWeakObjectPtr<APlayerController> BoundPlayerController;
};

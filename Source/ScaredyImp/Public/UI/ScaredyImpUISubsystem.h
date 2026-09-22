
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScaredyImpUISubsystem.generated.h"

class UScaredyImpUIConfig;
class UHUDWidget;
class AEnemyBase;
class APawn;

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

	void ShowGameplayHUD();
	void HideGameplayHUD();

	void ShowBossStatus(AEnemyBase* Boss);
	void HideBossStatus();

private:
	void BindToPlayerController(APlayerController* PlayerController);
	void UnbindFromPlayerController();

	UFUNCTION()
	void OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn);

private:
	EScaredyImpUIContext CurrentUIContext = EScaredyImpUIContext::None;

	UPROPERTY(Transient)
	TObjectPtr<UScaredyImpUIConfig> UIConfig;

	UPROPERTY(Transient)
	TObjectPtr<UHUDWidget> GameplayHUDWidget;

	TWeakObjectPtr<APlayerController> BoundPlayerController;
};

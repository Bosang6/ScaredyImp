
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class AScaredyImpCharacter;
class UPlayerStatusWidget;
class AEnemyBase;
class UBossStatusWidget;
class UOverlay;

UCLASS()
class SCAREDYIMP_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToCharacter(AScaredyImpCharacter* Character);
	void UnbindFromCharacter();

	void ShowBossStatus(AEnemyBase* Boss);
	void HideBossStatus();

	void ShowNotification(UUserWidget* NotificationWidget);
	void RemoveNotification(UUserWidget* NotificationWidget);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPlayerStatusWidget> PlayerStatusWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBossStatusWidget> BossStatusWidget;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> NotificationLayer;
};

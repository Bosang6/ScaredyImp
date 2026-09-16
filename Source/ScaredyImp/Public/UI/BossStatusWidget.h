
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BossStatusWidget.generated.h"

class AEnemyBase;
class UHealthBarWidget;
class UHealthComponent;

UCLASS()
class SCAREDYIMP_API UBossStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToBoss(AEnemyBase* Boss);
	void UnbindFromBoss();

protected:
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnHealthChanged(int32 CurrentHealth, int32 MaxHealth);

	UFUNCTION()
	void OnBossDeath();
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthBarWidget> HealthBarWidget;

	UPROPERTY()
	TObjectPtr<UHealthComponent> BoundHealthComponent;
};

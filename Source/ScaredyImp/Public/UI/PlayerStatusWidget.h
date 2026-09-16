
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

class AScaredyImpCharacter;
class UHealthBarWidget;
class UHealthComponent;
class UCoinWidget;
class UCoinComponent;

UCLASS()
class SCAREDYIMP_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToCharacter(AScaredyImpCharacter* Character);
	void UnbindFromCharacter();

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnHealthChanged(int32 CurrentHealth, int32 MaxHealth);

	UFUNCTION()
	void OnCoinChanged(int32 CurrentCoin);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthBarWidget> HealthBarWidget;

	UPROPERTY()
	TObjectPtr<UHealthComponent> BoundHealthComponent;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCoinWidget> CoinWidget;

	UPROPERTY()
	TObjectPtr<UCoinComponent> BoundCoinComponent;
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

class AScaredyImpCharacter;
class UHealthBarWidget;
class UHealthComponent;

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
	void OnCoinChanged();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthBarWidget> HealthBarWidget;

	UPROPERTY()
	TObjectPtr<UHealthComponent> BoundHealthComponent;
};


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

class AScaredyImpCharacter;
class UHealthBarWidget;

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
	void OnHealthChanged();

	UFUNCTION()
	void OnCoinChanged();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthBarWidget> HealthBarWidget;

};

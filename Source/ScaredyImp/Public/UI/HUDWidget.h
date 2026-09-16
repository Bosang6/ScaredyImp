
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class AScaredyImpCharacter;
class UPlayerStatusWidget;

UCLASS()
class SCAREDYIMP_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToCharacter(AScaredyImpCharacter* Character);

	void UnbindFromCharacter();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPlayerStatusWidget> PlayerStatusWidget;
	
};

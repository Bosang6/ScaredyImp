
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CoinWidget.generated.h"

class UTextBlock;

UCLASS()
class SCAREDYIMP_API UCoinWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCoinCount(int32 CoinCount);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CoinText;
};
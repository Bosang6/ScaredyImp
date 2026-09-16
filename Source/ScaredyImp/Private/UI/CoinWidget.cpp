
#include "UI/CoinWidget.h"
#include "Components/TextBlock.h"

void UCoinWidget::SetCoinCount(int32 CoinCount)
{
	if (!IsValid(CoinText)) return;

	CoinText->SetText(FText::AsNumber(CoinCount));
}
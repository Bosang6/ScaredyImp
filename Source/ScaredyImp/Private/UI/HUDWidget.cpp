

#include "UI/HUDWidget.h"
#include "UI/PlayerStatusWidget.h"
#include "ScaredyImpCharacter.h"

void UHUDWidget::BindToCharacter(AScaredyImpCharacter* Character)
{
	if (!IsValid(PlayerStatusWidget)) return;

	PlayerStatusWidget->BindToCharacter(Character);
}

void UHUDWidget::UnbindFromCharacter()
{
	if (!IsValid(PlayerStatusWidget)) return;

	PlayerStatusWidget->UnbindFromCharacter();
}

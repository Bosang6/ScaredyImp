

#include "UI/HUDWidget.h"
#include "UI/PlayerStatusWidget.h"
#include "UI/BossStatusWidget.h"
#include "Enemies/EnemyBase.h"
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

void UHUDWidget::ShowBossStatus(AEnemyBase* Boss)
{
	if (!IsValid(BossStatusWidget) || !IsValid(Boss)) return;

	BossStatusWidget->BindToBoss(Boss);
	BossStatusWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UHUDWidget::HideBossStatus()
{
	if (!IsValid(BossStatusWidget)) return;

	BossStatusWidget->UnbindFromBoss();
	BossStatusWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HideBossStatus();
}


#include "UI/BossStatusWidget.h"
#include "UI/HealthBarWidget.h"
#include "Enemies/EnemyBase.h"
#include "Comps/HealthComponent.h"

void UBossStatusWidget::BindToBoss(AEnemyBase* Boss)
{
	if (!IsValid(Boss)) return;

	// Avoid duplicate binding
	UnbindFromBoss();

	BoundHealthComponent = Boss->GetHealthComponent();
	if (!IsValid(BoundHealthComponent)) return;

	BoundHealthComponent->OnHealthChanged.AddDynamic(this, &UBossStatusWidget::OnHealthChanged);
	BoundHealthComponent->OnDeath.AddDynamic(this, &UBossStatusWidget::OnBossDeath);

	if (!IsValid(HealthBarWidget)) return;
	HealthBarWidget->SetHealth(
		BoundHealthComponent->GetCurrentHealth(),
		BoundHealthComponent->GetMaxHealth()
	);
}

void UBossStatusWidget::UnbindFromBoss()
{
	if (!IsValid(BoundHealthComponent)) return;

	BoundHealthComponent->OnHealthChanged.RemoveDynamic(this, &UBossStatusWidget::OnHealthChanged);
	BoundHealthComponent->OnDeath.RemoveDynamic(this, &UBossStatusWidget::OnBossDeath);
	BoundHealthComponent = nullptr;
}

void UBossStatusWidget::NativeDestruct()
{
	UnbindFromBoss();

	Super::NativeDestruct();
}

void UBossStatusWidget::OnHealthChanged(int32 CurrentHealth, int32 MaxHealth)
{
	if (!IsValid(BoundHealthComponent) || !IsValid(HealthBarWidget)) return;

	HealthBarWidget->SetHealth(CurrentHealth, MaxHealth);
}

void UBossStatusWidget::OnBossDeath()
{
	UnbindFromBoss();
}


#include "UI/PlayerStatusWidget.h"
#include "UI/HealthBarWidget.h"
#include "ScaredyImpCharacter.h"
#include "Comps/HealthComponent.h"

void UPlayerStatusWidget::BindToCharacter(AScaredyImpCharacter* Character)
{
	if (!IsValid(Character)) return;

	// Avoid duplicate binding
	UnbindFromCharacter();

	BoundHealthComponent = Character->GetHealthComponent();
	if (!IsValid(BoundHealthComponent)) return;

	BoundHealthComponent->OnHealthChanged.AddDynamic(this, &UPlayerStatusWidget::OnHealthChanged);

	// Init UI
	if (!IsValid(HealthBarWidget)) return;
	
	HealthBarWidget->SetHealth(
		BoundHealthComponent->GetCurrentHealth(),
		BoundHealthComponent->GetMaxHealth()
	);
}

void UPlayerStatusWidget::UnbindFromCharacter()
{
	if (!IsValid(BoundHealthComponent)) return;

	BoundHealthComponent->OnHealthChanged.RemoveDynamic(this, &UPlayerStatusWidget::OnHealthChanged);
	BoundHealthComponent = nullptr;
}

void UPlayerStatusWidget::NativeConstruct()
{
	UnbindFromCharacter();

	Super::NativeConstruct();
}

void UPlayerStatusWidget::OnHealthChanged(int32 CurrentHealth, int32 MaxHealth)
{
	if (!IsValid(BoundHealthComponent) || !IsValid(HealthBarWidget)) return;

	HealthBarWidget->SetHealth(CurrentHealth, MaxHealth);
}

void UPlayerStatusWidget::OnCoinChanged()
{
}

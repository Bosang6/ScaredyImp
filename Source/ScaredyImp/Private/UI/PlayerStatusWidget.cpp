
#include "UI/PlayerStatusWidget.h"
#include "UI/HealthBarWidget.h"
#include "UI/CoinWidget.h"
#include "ScaredyImpCharacter.h"
#include "Comps/HealthComponent.h"
#include "Comps/CoinComponent.h"

void UPlayerStatusWidget::BindToCharacter(AScaredyImpCharacter* Character)
{
	if (!IsValid(Character)) return;

	// Avoid duplicate binding
	UnbindFromCharacter();

	// ======================= Health =============================================
	BoundHealthComponent = Character->GetHealthComponent();
	if (IsValid(BoundHealthComponent))
	{
		BoundHealthComponent->OnHealthChanged.AddDynamic(this, &UPlayerStatusWidget::OnHealthChanged);

		if (IsValid(HealthBarWidget))
		{
			HealthBarWidget->SetHealth(
				BoundHealthComponent->GetCurrentHealth(),
				BoundHealthComponent->GetMaxHealth()
			);
		}
	}

	// ======================= Coin =============================================
	BoundCoinComponent = Character->GetCoinComponent();
	if (IsValid(BoundCoinComponent))
	{
		BoundCoinComponent->OnCoinChanged.AddDynamic(this, &UPlayerStatusWidget::OnCoinChanged);
	
		if (IsValid(CoinWidget))
		{
			CoinWidget->SetCoinCount(BoundCoinComponent->GetCoinCount());
		}
	}
}

void UPlayerStatusWidget::UnbindFromCharacter()
{
	if (!IsValid(BoundHealthComponent)) return;

	BoundHealthComponent->OnHealthChanged.RemoveDynamic(this, &UPlayerStatusWidget::OnHealthChanged);
	BoundHealthComponent = nullptr;

	BoundCoinComponent->OnCoinChanged.RemoveDynamic(this, &UPlayerStatusWidget::OnCoinChanged);
	BoundCoinComponent = nullptr;
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

void UPlayerStatusWidget::OnCoinChanged(int32 CurrentCoin)
{
	if (!IsValid(BoundCoinComponent) || !IsValid(CoinWidget)) return;

	CoinWidget->SetCoinCount(CurrentCoin);
}

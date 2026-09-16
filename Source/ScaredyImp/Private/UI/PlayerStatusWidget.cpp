
#include "UI/PlayerStatusWidget.h"
#include "UI/HealthBarWidget.h"

void UPlayerStatusWidget::BindToCharacter(AScaredyImpCharacter* Character)
{
}

void UPlayerStatusWidget::UnbindFromCharacter()
{
}

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UE_LOG(LogTemp, Warning, TEXT("PlayerStatusWidget NativeConstruct"));

	if (IsValid(HealthBarWidget))
	{
		HealthBarWidget->SetHealth(5, 5);
	}
}

void UPlayerStatusWidget::OnHealthChanged()
{
}

void UPlayerStatusWidget::OnCoinChanged()
{
}

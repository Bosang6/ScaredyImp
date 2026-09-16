
#include "UI/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealth(int32 CurrentHealth, int32 MaxHealth)
{
	if (!IsValid(HealthProgressBar)) return;

	const float HealthPercent = MaxHealth > 0 ? static_cast<float>(CurrentHealth) / static_cast<float>(MaxHealth) : 0.0f;

	HealthProgressBar->SetPercent(FMath::Clamp(HealthPercent, 0.0f, 1.0f));
}

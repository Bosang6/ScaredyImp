
#include "Comps/Character/HealthComponent.h"
#include "HealthComponent.h"
#include "ScaredyImp.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::ApplyDamage(int32 DamageAmount)
{
	if (DamageAmount <= 0)
	{
		UE_LOG(LogScaredyImp, Warning, TEXT("[ApplyDamage] DamageAmount: %d must be greater than 0."), DamageAmount);
		return;
	}

	CurrentHealth = FMath::Clamp(
		CurrentHealth - DamageAmount,
		0,
		MaxHealth
	);
}

bool UHealthComponent::IsDead() const
{
	return CurrentHealth <= 0;
}

void UHealthComponent::Heal(int32 HealAmount)
{
	if (HealAmount <= 0)
	{
		UE_LOG(LogScaredyImp, Warning, TEXT("[Heal] HealAmount: %d must be greater than 0."), HealAmount);
		return;
	}

	CurrentHealth = FMath::Clamp(
		CurrentHealth + HealAmount,
		0,
		MaxHealth
	);

}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}


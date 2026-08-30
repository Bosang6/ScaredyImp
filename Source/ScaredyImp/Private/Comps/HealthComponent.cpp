
#include "Comps/HealthComponent.h"
#include "ScaredyImp.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::ApplyDamage(int32 DamageAmount)
{
	if (!bIsInitialized || DamageAmount <= 0.0f || IsDead())
	{
		return;
	}

	CurrentHealth = FMath::Clamp(
		CurrentHealth - DamageAmount,
		0,
		MaxHealth
	);


	// Broadcast when a character dies
	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else
	{
		OnDamaged.Broadcast();
	}

	UE_LOG(LogScaredyImp, Warning, TEXT("Current HP: %d"), CurrentHealth);
}

bool UHealthComponent::IsDead() const
{
	return bIsInitialized && CurrentHealth <= 0;
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

	InitComponent();
}

void UHealthComponent::InitComponent()
{
	CurrentHealth = MaxHealth;

	bIsInitialized = true;
}


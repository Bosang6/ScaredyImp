
#include "Pickups/HeartPickup.h"
#include "ScaredyImpCharacter.h"
#include "GameFramework/Character.h"
#include "Comps/HealthComponent.h"

bool AHeartPickup::TryPickup(ACharacter* Character)
{
	AScaredyImpCharacter* Player = Cast<AScaredyImpCharacter>(Character);
	if (!IsValid(Player)) return false;

	UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
	if (!IsValid(HealthComponent)) return false;

	HealthComponent->Heal(HealAmount);

	return true;
}

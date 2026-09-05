
#include "Pickups/CoinPickup.h"
#include "ScaredyImpCharacter.h"
#include "GameFramework/Character.h"
#include "Comps/CoinComponent.h"

bool ACoinPickup::TryPickup(ACharacter* Character)
{
	AScaredyImpCharacter* Player = Cast<AScaredyImpCharacter>(Character);
	if (!IsValid(Player)) return false;

	UCoinComponent* CoinComponent = Player->FindComponentByClass<UCoinComponent>();
	if (!IsValid(CoinComponent)) return false;

	CoinComponent->AddCoin();

	return true;
}

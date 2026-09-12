

#include "Pickups/GameEndPickup.h"
#include "GameFramework/Character.h"

bool AGameEndPickup::TryPickup(ACharacter* Character)
{
	if (!IsValid(Character)) return false;

	OnGameEnded.Broadcast();

	return true;
}

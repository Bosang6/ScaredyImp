
#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "CoinPickup.generated.h"

class ACharacter;

UCLASS()
class SCAREDYIMP_API ACoinPickup : public APickupBase
{
	GENERATED_BODY()

protected:
	virtual bool TryPickup(ACharacter* Character) override;
};

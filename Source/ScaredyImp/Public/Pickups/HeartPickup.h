
#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "HeartPickup.generated.h"

class ACharacter;

UCLASS()
class SCAREDYIMP_API AHeartPickup : public APickupBase
{
	GENERATED_BODY()
	
protected:
	virtual bool TryPickup(ACharacter* Character) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	int32 HealAmount = 1;
};

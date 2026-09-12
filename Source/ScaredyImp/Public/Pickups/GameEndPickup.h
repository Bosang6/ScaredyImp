
#pragma once

#include "CoreMinimal.h"
#include "Pickups/PickupBase.h"
#include "GameEndPickup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameEnded);

UCLASS()
class SCAREDYIMP_API AGameEndPickup : public APickupBase
{
	GENERATED_BODY()

protected:
	virtual bool TryPickup(ACharacter* Character) override;
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Pickup|Game End")
	FOnGameEnded OnGameEnded;
};

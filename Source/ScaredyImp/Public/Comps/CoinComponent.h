
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinComponent.generated.h"

class UHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API UCoinComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCoinComponent();

	UFUNCTION(BlueprintCallable, Category = "Coin")
	void AddCoin(int32 Amount = 1);

	UFUNCTION(BlueprintCallable, Category = "Coin")
	int32 GetCoinCount() const { return CoinCount; };

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Coin", meta = (ClampMin = "1"))
	int32 CoinPerHeal = 10;

	UPROPERTY(VisibleInstanceOnly, Category = "Coin")
	int32 CoinCount = 0;

	UPROPERTY()
	TObjectPtr<UHealthComponent> HealthComponent;
};

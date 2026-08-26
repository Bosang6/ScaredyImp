#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth = 0;

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(int32 DamageAmount);

	bool IsDead() const;
	
	UFUNCTION(BlueprintCallable)
	void Heal(int32 HealAmount);

	// Getters
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentHealth() const { return CurrentHealth; };
	
	int32 GetMaxHealth() const { return MaxHealth; };

protected:
	virtual void BeginPlay() override;
};

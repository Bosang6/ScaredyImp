#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

// ========== Delegates ==============
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDamaged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	bool bIsInitialized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 MaxHealth = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	int32 CurrentHealth = 0;

public:	
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void ApplyDamage(int32 DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const;
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void Heal(int32 HealAmount);

	// Getters
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetCurrentHealth() const { return CurrentHealth; };
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	int32 GetMaxHealth() const { return MaxHealth; };

	// ========== Delegates ==============
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnDamaged OnDamaged;



protected:
	virtual void BeginPlay() override;

	virtual void InitComponent();
};

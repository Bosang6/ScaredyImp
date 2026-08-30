
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Stompable.h"
#include "EnemyBase.generated.h"

class UHealthComponent;
class UBoxComponent;

UCLASS()
class SCAREDYIMP_API AEnemyBase : public ACharacter, public IStompable
{
	GENERATED_BODY()

public:
	AEnemyBase();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDeath();

	UFUNCTION()
	void OnDamaged();

	UFUNCTION()
	void OnAttackHitBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interfaces Implementation
	virtual void ReceiveStomp_Implementation(AActor* Stomper, int32 DamageAmount) override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Attack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndAttack();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void OnAttackHit();

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool IsAttacking() const { return bIsAttacking; }

	UFUNCTION(BlueprintPure, Category = "Combat")
	bool IsHit() const { return bIsHit; }

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndHit();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> StompZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	TObjectPtr<UBoxComponent> AttackHitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Death")
	float DestroyDelay = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	int32 AttackDamage = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	bool bIsHit = false;

	// Each attack will only be counted once.
	UPROPERTY(Transient)
	TSet<TObjectPtr<AActor>> HitActorsThisAttack;

	FTimerHandle DestroyTimeHandle;
};

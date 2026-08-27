
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

public:	
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Interfaces Implementation
	virtual void ReceiveStomp_Implementation(AActor* Stomper, int32 DamageAmount) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> StompZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UHealthComponent> HealthComponent;

};

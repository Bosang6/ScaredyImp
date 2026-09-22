
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossEncounter.generated.h"

class ABlockingWall;
class UBoxComponent;
class ACharacter;
class UHealthComponent;
class AEnemyBase;
class UScaredyImpUISubsystem;

UCLASS()
class SCAREDYIMP_API ABossEncounter : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossEncounter();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBossDeath();
	UFUNCTION()
	void OnPlayerDeath();

	void StartEncounter(ACharacter* PlayerCharacter);
	void ResetEncounter();
	void ActivateWalls();
	void DeactivateWalls();

	UFUNCTION()
	void OnTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:
	void ShowBossHUD();
	void HideBossHUD();

protected:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Boss Encounter")
	TObjectPtr<AEnemyBase> Boss;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Boss Encounter")
	TArray<TObjectPtr<ABlockingWall>> BlockingWalls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss Encounter")
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY()
	TObjectPtr<UHealthComponent> PlayerHealthComponent;

	UPROPERTY()
	TObjectPtr<UScaredyImpUISubsystem> UISubsystem;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Boss Encounter")
	bool bEncounterStarted = false;
};

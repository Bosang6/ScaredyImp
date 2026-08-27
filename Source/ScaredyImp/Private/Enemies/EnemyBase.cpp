
#include "Enemies/EnemyBase.h"
#include "Comps/HealthComponent.h"
#include "ScaredyImp.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBase::ReceiveStomp_Implementation(AActor* Stomper, int32 DamageAmount)
{
	if (!HealthComponent)
	{
		return;
	}

	HealthComponent->ApplyDamage(DamageAmount);

	UE_LOG(
		LogScaredyImp,
		Warning,
		TEXT("[EnemyBase] Stomped by %s | Damage: %d | Health: %d"),
		*GetNameSafe(Stomper),
		DamageAmount,
		HealthComponent->GetCurrentHealth()
	);
}


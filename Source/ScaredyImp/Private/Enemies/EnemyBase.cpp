
#include "Enemies/EnemyBase.h"
#include "Comps/HealthComponent.h"
#include "ScaredyImp.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"

AEnemyBase::AEnemyBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StompZone = CreateDefaultSubobject<UBoxComponent>(TEXT("StompZone"));
	StompZone->SetupAttachment(GetCapsuleComponent());
	StompZone->SetBoxExtent(FVector(35.0f, 35.0f, 10.0f));
	StompZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StompZone->SetGenerateOverlapEvents(true);
	StompZone->SetCollisionResponseToAllChannels(ECR_Overlap);

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(HealthComponent))
	{
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	}
	
}

void AEnemyBase::OnDeath()
{
	// Disable Movement
	if (TObjectPtr<UCharacterMovementComponent> MovementComponent = GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
		MovementComponent->DisableMovement();
	}

	// Disable Capsule collision
	if (TObjectPtr<UCapsuleComponent> CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Disable StompZone collision
	if (IsValid(StompZone))
	{
		StompZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Destroy enemy after death animation
	SetLifeSpan(DestroyDelay);
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

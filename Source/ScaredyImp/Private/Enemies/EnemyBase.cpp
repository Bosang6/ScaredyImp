
#include "Enemies/EnemyBase.h"
#include "Comps/HealthComponent.h"
#include "ScaredyImp.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Comps/HealthComponent.h"

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

	AttackHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackHitBox"));
	AttackHitBox->SetupAttachment(GetMesh(), TEXT("AttackSocket"));
	AttackHitBox->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	AttackHitBox->SetGenerateOverlapEvents(true);
	AttackHitBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttackHitBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(HealthComponent))
	{
		HealthComponent->OnDeath.AddDynamic(this, &AEnemyBase::OnDeath);
	}

	if (IsValid(AttackHitBox))
	{
		AttackHitBox->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnAttackHitBoxBeginOverlap);
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

void AEnemyBase::OnAttackHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsAttacking) return;

	if (!IsValid(OtherActor) || OtherActor == this) return;

	if (HitActorsThisAttack.Contains(OtherActor)) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (OtherActor != PlayerPawn) return;

	// First Hit
	HitActorsThisAttack.Add(OtherActor);

	// Apply Damage to Character
	UHealthComponent* TargetHealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
	if (!IsValid(TargetHealthComponent)) return;
	TargetHealthComponent->ApplyDamage(AttackDamage);

	UE_LOG(LogScaredyImp, Warning, TEXT("[Enemy: %s] AttackHitBox Hit: %s"), *GetName(), *OtherActor->GetName());
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

void AEnemyBase::Attack()
{
	if (bIsAttacking) return;

	bIsAttacking = true;

	// A new attack begins, clearing the hit record of the previous attack.
	HitActorsThisAttack.Empty();

	if (IsValid(AttackHitBox))
	{
		AttackHitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	UE_LOG(LogScaredyImp, Warning, TEXT("[Enemy: %s] Attack started"), *GetName());
}

void AEnemyBase::EndAttack()
{
	if (!bIsAttacking) return;

	bIsAttacking = false;

	if (IsValid(AttackHitBox))
	{
		AttackHitBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UE_LOG(LogScaredyImp, Warning, TEXT("[Enemy: %s] Attack ended"), *GetName());
}

void AEnemyBase::OnAttackHit()
{
	if (!bIsAttacking) return;

	UE_LOG(LogScaredyImp, Warning, TEXT("[Enemy: %s] Attack Hit"), *GetName());
}

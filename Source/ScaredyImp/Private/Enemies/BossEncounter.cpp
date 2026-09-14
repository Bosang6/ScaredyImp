
#include "Enemies/BossEncounter.h"
#include "Obstacle/BlockingWall.h"
#include "Comps/HealthComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

ABossEncounter::ABossEncounter()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABossEncounter::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABossEncounter::OnTriggerBeginOverlap);

	if (!IsValid(Boss)) return;
	
	UHealthComponent* HealthComponent = Boss->FindComponentByClass<UHealthComponent>();

	if (!HealthComponent) return;

	HealthComponent->OnDeath.AddDynamic(this, &ABossEncounter::OnBossDeath);
}

void ABossEncounter::OnBossDeath()
{
	DeactivateWalls();
}

void ABossEncounter::OnPlayerDeath()
{
	ResetEncounter();
}

void ABossEncounter::StartEncounter(ACharacter* PlayerCharacter)
{
	if (bEncounterStarted) return;

	bEncounterStarted = true;

	ActivateWalls();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PlayerHealthComponent = PlayerCharacter->FindComponentByClass<UHealthComponent>();

	if (IsValid(PlayerHealthComponent))
	{
		PlayerHealthComponent->OnDeath.AddUniqueDynamic(this, &ABossEncounter::OnPlayerDeath);
	}
}

void ABossEncounter::ResetEncounter()
{
	bEncounterStarted = false;

	DeactivateWalls();

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	if (IsValid(PlayerHealthComponent))
	{
		PlayerHealthComponent->OnDeath.RemoveDynamic(this, &ABossEncounter::OnPlayerDeath);

		PlayerHealthComponent = nullptr;
	}
}

void ABossEncounter::ActivateWalls()
{
	for (ABlockingWall* Wall : BlockingWalls)
	{
		if (IsValid(Wall))
		{
			Wall->ActivateWall();
		}
	}
}

void ABossEncounter::DeactivateWalls()
{
	for (ABlockingWall* Wall : BlockingWalls)
	{
		if (IsValid(Wall))
		{
			Wall->DeactivateWall();
		}
	}
}

void ABossEncounter::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bEncounterStarted) return;

	ACharacter* Character = Cast<ACharacter>(OtherActor);

	if (!Character || !Character->IsPlayerControlled()) return;

	StartEncounter(Character);
}
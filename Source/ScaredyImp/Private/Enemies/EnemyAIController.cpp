// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/EnemyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Components/StateTreeAIComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "ScaredyImp.h"

AEnemyAIController::AEnemyAIController()
{
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));

	StateTreeAIComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeAIComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	SightConfig->SightRadius = 800.0f;
	SightConfig->LoseSightRadius = 1000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->SetMaxAge(2.0f);
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	EnemyPerceptionComponent->ConfigureSense(*SightConfig);
	EnemyPerceptionComponent->SetDominantSense(
		SightConfig->GetSenseImplementation()
	);

	SetPerceptionComponent(*EnemyPerceptionComponent);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(EnemyPerceptionComponent))
	{
		EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetPerceptionUpdate);
	}
}

void AEnemyAIController::OnTargetPerceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	if (!IsValid(Actor)) return;

	// NPC only detects players.
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0); 
	if (Actor != PlayerPawn) return;

	// Player detecte
	if (Stimulus.WasSuccessfullySensed())
	{
		TargetActor = Actor;

		UE_LOG(LogScaredyImp, Warning, TEXT("[Enemy: %s] Player detected: %s"), *GetName(), *Actor->GetName());
	}
	else
	{
		if (TargetActor == Actor)
		{
			TargetActor = nullptr;
		}

		UE_LOG(LogScaredyImp, Warning, TEXT("[Enemy: %s] Player lost: %s"), *GetName(), *Actor->GetName());
	}

}

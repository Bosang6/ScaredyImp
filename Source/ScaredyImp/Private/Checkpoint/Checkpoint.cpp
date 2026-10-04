
#include "Checkpoint/Checkpoint.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Checkpoint/CheckpointSubsystem.h"
#include "GameFramework/Pawn.h"
#include "ScaredyImp.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "ScaredyImpCharacter.h"

ACheckpoint::ACheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
	TriggerBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	TriggerBox->SetGenerateOverlapEvents(true);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnTriggerBoxBeginOverlap);

	RespawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RespawnPoint"));
	RespawnPoint->SetupAttachment(Root);
}

void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACheckpoint::OnTriggerBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AScaredyImpCharacter* Character = Cast<AScaredyImpCharacter>(OtherActor);

	if (!IsValid(Character) || !Character->IsPlayerControlled()) return;

	UCheckpointSubsystem* CheckpointSubsystem = GetWorld()->GetSubsystem<UCheckpointSubsystem>();
	if (!IsValid(CheckpointSubsystem))
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[CheckpointSubsystem] CheckpointSubsystem not found."));
		return;
	}

	// Record checkpoint
	CheckpointSubsystem->ActivateCheckpoint(RespawnPoint->GetComponentTransform());

	// Auto Save Game
	if (UScaredyImpSaveSubsystem* SaveSubsystem = GetGameInstance()->GetSubsystem<UScaredyImpSaveSubsystem>())
	{
		SaveSubsystem->SaveAtCheckpoint(Character);
	}

	UE_LOG(LogScaredyImp, Warning, TEXT("[Checkpoint] Activate."));
}

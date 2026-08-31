
#include "Checkpoint/Checkpoint.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Checkpoint/CheckpointSubsystem.h"
#include "GameFramework/Pawn.h"
#include "ScaredyImp.h"

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
	APawn* Pawn = Cast<APawn>(OtherActor);

	if (!IsValid(Pawn) || !Pawn->IsPlayerControlled()) return;

	UCheckpointSubsystem* CheckpointSubsystem = GetWorld()->GetSubsystem<UCheckpointSubsystem>();
	if (!IsValid(CheckpointSubsystem))
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[CheckpointSubsystem] CheckpointSubsystem not found."));
		return;
	}

	// Record CheckpointData
	FCheckpointData CheckpointData;
	CheckpointData.RespawnTransform = RespawnPoint->GetComponentTransform();
	
	CheckpointSubsystem->ActivateCheckpoint(CheckpointData);

	UE_LOG(LogScaredyImp, Warning, TEXT("[Checkpoint] Activate."));
}

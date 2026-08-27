
#include "Comps/StompComponent.h"
#include "ScaredyImp.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Interfaces/Stompable.h"
#include "GameFramework/CharacterMovementComponent.h"

UStompComponent::UStompComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStompComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACharacter>(GetOwner());

	if (!Owner)
	{
		UE_LOG(LogScaredyImp, Warning, TEXT("[StompComponent] Owner must be a Character."));
		return;
	}

	// Create a StompBox for Owner
	StompBox = Cast<UBoxComponent>(Owner->AddComponentByClass(
		UBoxComponent::StaticClass(),
		true,
		FTransform::Identity,
		false
	));

	if (!StompBox)
	{
		UE_LOG(LogScaredyImp, Warning, TEXT("[StompComponent] Failed to create StompBox."));
		return;
	}

	Owner->AddInstanceComponent(StompBox);

	StompBox->AttachToComponent(
		Owner->GetRootComponent(),
		FAttachmentTransformRules::KeepRelativeTransform
	);
	StompBox->SetRelativeLocation(StompBoxRelativeLocation);
	StompBox->SetBoxExtent(StompBoxExtent);
	StompBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StompBox->SetGenerateOverlapEvents(true);
	StompBox->OnComponentBeginOverlap.AddDynamic(this, &UStompComponent::OnStompBoxBeginOverlap);

	UE_LOG(LogScaredyImp, Warning,
		TEXT("[StompComponent] StompBox created: %s"),
		*GetNameSafe(StompBox));
}

void UStompComponent::OnStompBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Owner)
	{
		return;
	}

	if (!OtherActor || OtherActor == Owner)
	{
		return;
	}

	UE_LOG(LogScaredyImp, Warning,
		TEXT("[StompComponent] OtherActor: %s"),
		*OtherActor->GetName());

	if (!OtherComp)
	{
		return;
	}

	// Owner must be in the air
	if (!Owner->GetCharacterMovement()->IsFalling())
	{
		return;
	}

	// OtherActors must implement the Stompable interface.
	if (!OtherActor->Implements<UStompable>())
	{
		return;
	}

	// Successful stomped
	IStompable::Execute_ReceiveStomp(
		OtherActor,
		Owner,
		StompDamage
	);
}


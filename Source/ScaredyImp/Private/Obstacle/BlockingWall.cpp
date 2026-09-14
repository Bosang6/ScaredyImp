
#include "Obstacle/BlockingWall.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Materials/MaterialInstanceDynamic.h"

ABlockingWall::ABlockingWall()
{
	PrimaryActorTick.bCanEverTick = false;

	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
	SetRootComponent(PlaneMesh);
	PlaneMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(PlaneMesh);
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void ABlockingWall::ActivateWall()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("OnOff"), 1.0f);
	}
}

void ABlockingWall::DeactivateWall()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("OnOff"), 0.0f);
	}
}

void ABlockingWall::BeginPlay()
{
	Super::BeginPlay();
	
	DynamicMaterial = PlaneMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(TEXT("OnOff"), 0.0f);
	}
}
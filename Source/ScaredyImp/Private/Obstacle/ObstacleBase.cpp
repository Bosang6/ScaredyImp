
#include "Obstacle/ObstacleBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

AObstacleBase::AObstacleBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ObstacleRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(ObstacleRoot);

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ObstacleMesh->SetupAttachment(ObstacleRoot);
	ObstacleMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}


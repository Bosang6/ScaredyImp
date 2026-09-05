
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UArrowComponent;

UCLASS()
class SCAREDYIMP_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	APortal();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal")
	TObjectPtr<UStaticMeshComponent> PortalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Portal")
	TObjectPtr<UBoxComponent> Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TObjectPtr<UArrowComponent> ExitPoint;
};

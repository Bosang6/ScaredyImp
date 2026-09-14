
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlockingWall.generated.h"

class StaticMeshComponent;
class UBoxComponent;
class UMaterialInstanceDynamic;

UCLASS()
class SCAREDYIMP_API ABlockingWall : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlockingWall();

	UFUNCTION(BlueprintCallable, Category = "Blocking Wall")
	void ActivateWall();

	UFUNCTION(BlueprintCallable, Category = "Blocking Wall")
	void DeactivateWall();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blocking Wall")
	TObjectPtr<UStaticMeshComponent> PlaneMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blocking Wall")
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Blocking Wall")
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial;
};

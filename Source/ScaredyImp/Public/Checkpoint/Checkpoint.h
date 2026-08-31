
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class SCAREDYIMP_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpoint();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checkpoint")
	TObjectPtr<USceneComponent> RespawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Checkpoint")
	FName Checkpoint = NAME_None;

};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoidVolume.generated.h"

class USceneComponent;
class UBoxComponent;

UCLASS()
class SCAREDYIMP_API AVoidVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AVoidVolume();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnVoidBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Void")
	TObjectPtr<USceneComponent> Root;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void")
	TObjectPtr<UBoxComponent> VoidBox;
};

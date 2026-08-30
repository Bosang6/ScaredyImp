
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StompComponent.generated.h"

class UBoxComponent;
class ACharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API UStompComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStompComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStompBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stomp")
	int32 StompDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stomp")
	float StompBounceHorizontalVelocity = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stomp")
	float StompBounceVerticalVelocity = 700.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stomp|Collision")
	FVector StompBoxRelativeLocation = FVector(0.0f, 0.0f, -95.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stomp|Collision")
	FVector StompBoxExtent = FVector(30.0f, 30.0f, 10.0f);

private: 
	UPROPERTY()
	TObjectPtr<UBoxComponent> StompBox;

	UPROPERTY()
	TObjectPtr<ACharacter> Owner;
};

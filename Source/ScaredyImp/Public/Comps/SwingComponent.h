
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "SwingComponent.generated.h"

class UStaticMeshComponent;

UENUM(BlueprintType)
enum class ESwingAxis : uint8
{
	Pitch,
	Yaw,
	Roll
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API USwingComponent : public UMovementComponent
{
	GENERATED_BODY()

public:	
	USwingComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Maximum rotation angle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swing")
	float MaxSwingAngle = 60.0f;

	// Time required for one complete swing cycle
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swing", meta = (ClampMin = "0.01"))
	float SwingPeriod = 3.0f;

	// Initial position in the swing cycle [0, 1]
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swing", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float StartAlpha = 0.0f;

	// Axis used for swinging
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Swing")
	ESwingAxis SwingAxis = ESwingAxis::Pitch;

private:
	//UPROPERTY()
	//TObjectPtr<UStaticMeshComponent> TargetMesh;

	FRotator InitialRotation;

	float ElapsedTime = 0.0f;
};

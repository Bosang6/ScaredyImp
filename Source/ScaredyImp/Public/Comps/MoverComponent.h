
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SCAREDYIMP_API UMoverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMoverComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector LocalStart = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector LocalEnd = FVector(0.0f, 300.0f, 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float StartAlpha = 0.0f;
		
private:
	FVector WorldStart;
	FVector WorldEnd;

	// Current phase used by the sine function
	float Phase = 0.0f;
};

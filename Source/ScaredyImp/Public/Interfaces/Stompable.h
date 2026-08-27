
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Stompable.generated.h"

UINTERFACE(MinimalAPI)
class UStompable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SCAREDYIMP_API IStompable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Stomp")
	void ReceiveStomp(AActor* Stomper, int32 DamageAmount);
};

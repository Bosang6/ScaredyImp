
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "VoidRecoverable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UVoidRecoverable : public UInterface
{
	GENERATED_BODY()
};


class SCAREDYIMP_API IVoidRecoverable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Void")
	void HandleVoid();
};

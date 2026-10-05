
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScaredyImpFunctionLibrary.generated.h"

class UScaredyImpSaveSubsystem;

UCLASS()
class SCAREDYIMP_API UScaredyImpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "ScaredyImp|Save")
	static UScaredyImpSaveSubsystem* GetSaveSubsystem(const UObject* WorldContextObject);
};

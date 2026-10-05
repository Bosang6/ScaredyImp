
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ScaredyImpFunctionLibrary.generated.h"

class UScaredyImpSaveSubsystem;
class UScaredyImpGameFlowSubsystem;

UCLASS()
class SCAREDYIMP_API UScaredyImpFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/*
	* meta = (WorldContext = "WorldContextObject")
	* When this function is called within a Blueprint, UE will automatically use the current Blueprint's World Context.
	*/ 
	UFUNCTION(BlueprintPure, Category = "ScaredyImp|Save", meta = (WorldContext = "WorldContextObject"))
	static UScaredyImpSaveSubsystem* GetSaveSubsystem(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "ScaredyImp|Game Flow", meta = (WorldContext = "WorldContextObject"))
	static UScaredyImpGameFlowSubsystem* GetGameFlowSubsystem(const UObject* WorldContextObject);
};

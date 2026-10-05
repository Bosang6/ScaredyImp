
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScaredyImpGameFlowSubsystem.generated.h"

UCLASS()
class SCAREDYIMP_API UScaredyImpGameFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool StartNewGame(const TSoftObjectPtr<UWorld>& GameplayLevel);
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool ContinueGame(const TSoftObjectPtr<UWorld>& GameplayLevel);

private:
	bool OpenGameplayLevel(const TSoftObjectPtr<UWorld>& GameplayLevel);
};

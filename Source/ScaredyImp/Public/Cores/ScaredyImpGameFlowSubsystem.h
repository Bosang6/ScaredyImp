
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScaredyImpGameFlowSubsystem.generated.h"

class UScaredyImpGameFlowConfig;

UCLASS()
class SCAREDYIMP_API UScaredyImpGameFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool StartNewGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool ContinueGame();

private:
	bool OpenGameplayLevel();

	const UScaredyImpGameFlowConfig* GetGameFlowConfig() const;
};

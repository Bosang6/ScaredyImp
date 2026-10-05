
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScaredyImpGameFlowSubsystem.generated.h"

UCLASS()
class SCAREDYIMP_API UScaredyImpGameFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	bool StartNewGame(const TSoftObjectPtr<UWorld>& GameplayLevel);
	
	bool ContinueGame(const TSoftObjectPtr<UWorld>& GameplayLevel);

private:
	bool OpenGameplayLevel(const TSoftObjectPtr<UWorld>& GameplayLevel);
};

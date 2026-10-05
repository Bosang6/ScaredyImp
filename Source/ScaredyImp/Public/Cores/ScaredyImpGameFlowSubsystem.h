
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScaredyImpGameFlowSubsystem.generated.h"

class UScaredyImpGameFlowConfig;
class APlayerController;

UCLASS()
class SCAREDYIMP_API UScaredyImpGameFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool StartNewGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool ContinueGame();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool ReturnToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	bool CompleteGame(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "Game Flow")
	void QuitGame();

private:
	bool OpenGameplayLevel();
	bool OpenMainMenu();

	bool OpenLevel(const TSoftObjectPtr<UWorld>& Level);

	const UScaredyImpGameFlowConfig* GetGameFlowConfig() const;
};

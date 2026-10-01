
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ScaredyImpSaveSubsystem.generated.h"

class UScaredyImpSaveGame;

UCLASS()
class SCAREDYIMP_API UScaredyImpSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Save")
	bool HasSaveGame() const;

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool LoadSaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool DeleteSaveGame();
	
private:
	TObjectPtr<UScaredyImpSaveGame> CurrentSaveGame;

	static const FString SaveSlotName;
	static constexpr int32 UserIndex = 0;
};

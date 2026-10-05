
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Save/ScaredyImpSaveGame.h"
#include "ScaredyImpSaveSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnGameSaved)

class UScaredyImpSaveGame;
class AScaredyImpCharacter;

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

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool SaveGame(const FScaredyImpPlayerSaveData& PlayerData);

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool SaveAtCheckpoint(AScaredyImpCharacter* Character);

	UFUNCTION(BlueprintCallable, Category = "Save")
	bool ApplySaveGame(AScaredyImpCharacter* Character);

public:
	FOnGameSaved OnGameSaved;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UScaredyImpSaveGame> CurrentSaveGame;

	bool bPendingApply = false;

	static const FString SaveSlotName;
	static constexpr int32 UserIndex = 0;
};

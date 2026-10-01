
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Save/ScaredyImpSaveGame.h"
#include "Kismet/GameplayStatics.h"

// game only supports one save
const FString UScaredyImpSaveSubsystem::SaveSlotName = TEXT("ScaredyImpSave");

bool UScaredyImpSaveSubsystem::HasSaveGame() const
{
	return UGameplayStatics::DoesSaveGameExist(
		SaveSlotName,
		UserIndex
	);
}

bool UScaredyImpSaveSubsystem::LoadSaveGame()
{
	if (!HasSaveGame())
	{
		CurrentSaveGame = nullptr;
		return false;
	}

	USaveGame* LoadedSaveGame = UGameplayStatics::LoadGameFromSlot(
		SaveSlotName,
		UserIndex
	);

	CurrentSaveGame = Cast<UScaredyImpSaveGame>(LoadedSaveGame);

	if (!IsValid(CurrentSaveGame)) return false;

	return true;
}

bool UScaredyImpSaveSubsystem::DeleteSaveGame()
{
	CurrentSaveGame = nullptr;

	if (!HasSaveGame()) return true;

	const bool bDeleted = UGameplayStatics::DeleteGameInSlot(
		SaveSlotName,
		UserIndex
	);

	if (!bDeleted) return false;

	return true;
}

bool UScaredyImpSaveSubsystem::SaveGame(const FScaredyImpPlayerSaveData& PlayerData)
{
	UScaredyImpSaveGame* SaveGameObject = Cast<UScaredyImpSaveGame>(
		UGameplayStatics::CreateSaveGameObject(
			UScaredyImpSaveGame::StaticClass()
		)
	);

	if (!IsValid(SaveGameObject)) return false;

	SaveGameObject->PlayerData = PlayerData;

	const bool bSaved = UGameplayStatics::SaveGameToSlot(
		SaveGameObject,
		SaveSlotName,
		UserIndex
	);

	if (!bSaved) return false;

	CurrentSaveGame = SaveGameObject;

	return true;
}

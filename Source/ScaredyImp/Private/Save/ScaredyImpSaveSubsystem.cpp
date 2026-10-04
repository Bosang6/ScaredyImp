
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Save/ScaredyImpSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "ScaredyImpCharacter.h"
#include "Comps/HealthComponent.h"
#include "Comps/CoinComponent.h"
#include "Checkpoint/CheckpointSubsystem.h"
#include "GameFramework/CharacterMovementComponent.h"

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
	bPendingApply = false;

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

	bPendingApply = true;

	return true;
}

bool UScaredyImpSaveSubsystem::DeleteSaveGame()
{
	CurrentSaveGame = nullptr;
	bPendingApply = false;

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

bool UScaredyImpSaveSubsystem::SaveAtCheckpoint(AScaredyImpCharacter* Character)
{
	if (!IsValid(Character)) return false;

	UHealthComponent* HealthCompoennt = Character->GetHealthComponent();
	UCoinComponent* CoinComponent = Character->GetCoinComponent();
	if (!IsValid(HealthCompoennt) || !IsValid(CoinComponent)) return false;

	UWorld* World = Character->GetWorld();
	if (!IsValid(World)) return false;

	UCheckpointSubsystem* CheckpointSubsystem = World->GetSubsystem<UCheckpointSubsystem>();
	if (!IsValid(CheckpointSubsystem)) return false;

	if (!CheckpointSubsystem->HasActiveCheckpoint()) return false;

	FScaredyImpPlayerSaveData PlayerData;
	PlayerData.Health = HealthCompoennt->GetCurrentHealth();
	PlayerData.Coins = CoinComponent->GetCoinCount();
	PlayerData.CheckpointTransform = CheckpointSubsystem->GetCurrentCheckpoint();

	return SaveGame(PlayerData);
}

bool UScaredyImpSaveSubsystem::ApplySaveGame(AScaredyImpCharacter* Character)
{
	if (!IsValid(CurrentSaveGame)) return false;
	if (!IsValid(Character)) return false;
	if (!bPendingApply) return false;

	UHealthComponent* HealthComponent = Character->GetHealthComponent();
	UCoinComponent* CoinComponent = Character->GetCoinComponent();
	if (!IsValid(HealthComponent) || !IsValid(CoinComponent)) return false;

	UWorld* World = Character->GetWorld();
	if (!IsValid(World)) return false;

	UCheckpointSubsystem* CheckpointSubsystem = World->GetSubsystem<UCheckpointSubsystem>();
	if (!IsValid(CheckpointSubsystem)) return false;

	const FScaredyImpPlayerSaveData& PlayerData = CurrentSaveGame->PlayerData;

	// Restore player state
	HealthComponent->RestoreHealth(PlayerData.Health);
	CoinComponent->RestoreCoinCount(PlayerData.Coins);
	CheckpointSubsystem->ActivateCheckpoint(PlayerData.CheckpointTransform);

	// Clear existing movement before relocating the player
	if (UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement())
	{
		MovementComponent->StopMovementImmediately();
	}

	// Restore player location
	Character->SetActorTransform(PlayerData.CheckpointTransform);

	// The loaded save has now been consumed.
	bPendingApply = false;

	UE_LOG(
		LogTemp,
		Log,
		TEXT("[SaveSubsystem] Save game applied.")
	);

	return true;
}


#include "Utilities/ScaredyImpFunctionLibrary.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Cores/ScaredyImpGameFlowSubsystem.h"
#include "UI/ScaredyImpUISubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/PlayerController.h"

UScaredyImpSaveSubsystem* UScaredyImpFunctionLibrary::GetSaveSubsystem(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;

	UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!IsValid(GameInstance)) return nullptr;

	return GameInstance->GetSubsystem<UScaredyImpSaveSubsystem>();
}

UScaredyImpGameFlowSubsystem* UScaredyImpFunctionLibrary::GetGameFlowSubsystem(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;

	UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!IsValid(GameInstance)) return nullptr;

	return GameInstance->GetSubsystem<UScaredyImpGameFlowSubsystem>();
}

UScaredyImpUISubsystem* UScaredyImpFunctionLibrary::GetUISubsystem(APlayerController* PlayerController)
{
	if (!IsValid(PlayerController)) return nullptr;

	return ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(PlayerController);
}

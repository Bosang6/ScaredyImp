
#include "Utilities/ScaredyImpFunctionLibrary.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Engine/GameInstance.h"
#include "Engine/World.h"

UScaredyImpSaveSubsystem* UScaredyImpFunctionLibrary::GetSaveSubsystem(const UObject* WorldContextObject)
{
	if (!IsValid(WorldContextObject)) return nullptr;

	UWorld* World = WorldContextObject->GetWorld();
	if (!IsValid(World)) return nullptr;

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!IsValid(GameInstance)) return nullptr;

	return GameInstance->GetSubsystem<UScaredyImpSaveSubsystem>();
}


#include "UI/ScaredyImpUISubsystem.h"
#include "GameFramework/PlayerController.h"

void UScaredyImpUISubsystem::Initialize(FSubsystemCollectionBase& CollectionBase)
{
	Super::Initialize(CollectionBase);

	UE_LOG(LogTemp, Log, TEXT("ScaredyImpUISubsystem initialized."));
}

void UScaredyImpUISubsystem::Deinitialize()
{
	UE_LOG(LogTemp, Log, TEXT("ScaredyImpUISubsystem deinitialized."));

	Super::Deinitialize();
}

void UScaredyImpUISubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	UE_LOG(
		LogTemp,
		Log,
		TEXT("ScaredyImpUISubsystem PlayerController changed: %s"),
		IsValid(NewPlayerController) ? *NewPlayerController->GetName() : TEXT("None")
	);

	APlayerController* CurrentPC = GetOwningPlayerController();

	UE_LOG(
		LogTemp,
		Log,
		TEXT("Current owning PlayerController: %s"),
		IsValid(CurrentPC)
		? *CurrentPC->GetName()
		: TEXT("None")
	);
}

APlayerController* UScaredyImpUISubsystem::GetOwningPlayerController() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (!IsValid(LocalPlayer)) return nullptr;
	
	return LocalPlayer->GetPlayerController(GetWorld());
}

void UScaredyImpUISubsystem::SetUIContext(EScaredyImpUIContext NewContext)
{
	if (CurrentUIContext == NewContext) return;

	CurrentUIContext = NewContext;

	UE_LOG(
		LogTemp,
		Log,
		TEXT("UI Context changed to: %s"),
		*UEnum::GetValueAsString(CurrentUIContext)
	);
}

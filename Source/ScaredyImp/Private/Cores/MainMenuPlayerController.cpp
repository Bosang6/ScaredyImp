
#include "Cores/MainMenuPlayerController.h"
#include "Engine/LocalPlayer.h"
#include "UI/ScaredyImpUISubsystem.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UScaredyImpUISubsystem* UISubsystem = ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(this))
	{
		UISubsystem->SetUIContext(EScaredyImpUIContext::MainMenu);
	}
}

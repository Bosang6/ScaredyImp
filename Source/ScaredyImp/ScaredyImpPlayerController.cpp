
#include "ScaredyImpPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ScaredyImp.h"
#include "ScaredyImpCharacter.h"
#include "UI/ScaredyImpUISubsystem.h"

void AScaredyImpPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UScaredyImpUISubsystem* UISubsystem =
		ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(this))
	{
		UISubsystem->SetUIContext(EScaredyImpUIContext::Gameplay);
	}

	if (!IsLocalPlayerController()) return;

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	bShowMouseCursor = false;
}

void AScaredyImpPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}
		}
	}
}

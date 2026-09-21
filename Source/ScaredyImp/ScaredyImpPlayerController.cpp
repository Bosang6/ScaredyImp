
#include "ScaredyImpPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ScaredyImp.h"
#include "UI/HUDWidget.h"
#include "ScaredyImpCharacter.h"
#include "Enemies/EnemyBase.h"
#include "Engine/LocalPlayer.h"
#include "UI/ScaredyImpUISubsystem.h"

void AScaredyImpPlayerController::ShowBossStatus(AEnemyBase* Boss)
{
	if (!IsValid(HUDWidget) || !IsValid(Boss)) return;

	HUDWidget->ShowBossStatus(Boss);
}

void AScaredyImpPlayerController::HideBossStatus()
{
	if (!IsValid(HUDWidget)) return;

	HUDWidget->HideBossStatus();
}

void AScaredyImpPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UScaredyImpUISubsystem* UISubsystem =
		ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(this))
	{
		UISubsystem->SetUIContext(EScaredyImpUIContext::Gameplay);
	}

	if (!IsLocalPlayerController()) return;

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetClass);

		if (IsValid(HUDWidget))
		{
			HUDWidget->AddToPlayerScreen(0);

			// Bind current character to HUD
			RefreshHUDBinding();
		}
		else
		{
			UE_LOG(LogScaredyImp, Error, TEXT("Could not spawn HUD widget."));
		}
	}

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

void AScaredyImpPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RefreshHUDBinding();
}

void AScaredyImpPlayerController::OnUnPossess()
{
	if (IsValid(HUDWidget))
	{
		HUDWidget->UnbindFromCharacter();
	}

	Super::OnUnPossess();
}

void AScaredyImpPlayerController::RefreshHUDBinding()
{
	if (!IsValid(HUDWidget)) return;

	AScaredyImpCharacter* PlayerCharacter = Cast<AScaredyImpCharacter>(GetPawn());
	if (!IsValid(PlayerCharacter)) return;

	HUDWidget->BindToCharacter(PlayerCharacter);
}

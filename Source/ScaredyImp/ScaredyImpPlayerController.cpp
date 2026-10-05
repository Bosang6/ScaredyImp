
#include "ScaredyImpPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "ScaredyImp.h"
#include "ScaredyImpCharacter.h"
#include "UI/ScaredyImpUISubsystem.h"
#include "EnhancedInputComponent.h"
#include "Save/ScaredyImpSaveSubsystem.h"
#include "Utilities/ScaredyImpFunctionLibrary.h"
#include "Cores/ScaredyImpGameFlowSubsystem.h"
#include "Pickups/GameEndPickup.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

void AScaredyImpPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UScaredyImpUISubsystem* UISubsystem =
		ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(this))
	{
		UISubsystem->SetUIContext(EScaredyImpUIContext::Gameplay);
	}

	if (!IsLocalPlayerController()) return;

	// There is only one GameEnd Pickup in the level
	AGameEndPickup* GameEndPickup = Cast<AGameEndPickup>(UGameplayStatics::GetActorOfClass(this, AGameEndPickup::StaticClass()));
	if (IsValid(GameEndPickup))
	{
		GameEndPickup->OnGameEnded.AddUniqueDynamic(this, &AScaredyImpPlayerController::OnGameCompleted);
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

	// Bind PlayerController input action
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	if (!IsValid(EnhancedInputComponent)) return;

	if (IsValid(PauseAction))
	{
		EnhancedInputComponent->BindAction(
			PauseAction,
			ETriggerEvent::Started,
			this,
			&AScaredyImpPlayerController::OnPausePressed
		);
	}
}

void AScaredyImpPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AScaredyImpCharacter* PlayerCharacter = Cast<AScaredyImpCharacter>(InPawn);
	if (!IsValid(PlayerCharacter)) return;

	// Avoid duplicate bindings.
	PlayerCharacter->OnCharacterReady.RemoveAll(this);

	// If the Character is already Ready, we don't need to wait for the Delegate.
	if (PlayerCharacter->IsCharacterReady())
	{
		OnCharacterReady(PlayerCharacter);
		return;
	}

	PlayerCharacter->OnCharacterReady.AddUObject(this, &AScaredyImpPlayerController::OnCharacterReady);
}

void AScaredyImpPlayerController::OnUnPossess()
{
	if (AScaredyImpCharacter* PlayerCharacter = Cast<AScaredyImpCharacter>(GetPawn()))
	{
		PlayerCharacter->OnCharacterReady.RemoveAll(this);
	}

	Super::OnUnPossess();
}

void AScaredyImpPlayerController::OnPausePressed()
{
	UScaredyImpUISubsystem* UISubsystem = ULocalPlayer::GetSubsystemFromController<UScaredyImpUISubsystem>(this);

	if (!IsValid(UISubsystem)) return;

	UISubsystem->ShowPauseMenu();
}

void AScaredyImpPlayerController::OnCharacterReady(AScaredyImpCharacter* InCharacter)
{
	if (!IsValid(InCharacter)) return;

	InCharacter->OnCharacterReady.RemoveAll(this);

	UScaredyImpSaveSubsystem* SaveSubsystem = UScaredyImpFunctionLibrary::GetSaveSubsystem(this);
	if (!IsValid(SaveSubsystem)) return;

	SaveSubsystem->ApplySaveGame(InCharacter);
}

void AScaredyImpPlayerController::OnGameCompleted()
{
	// Player stop moving
	AScaredyImpCharacter* PlayerCharacter = Cast<AScaredyImpCharacter>(GetPawn());
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->StopJumping();

		if (UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement())
		{
			Movement->StopMovementImmediately();
			Movement->DisableMovement();
		}

		SetIgnoreMoveInput(true);
	}

	UScaredyImpGameFlowSubsystem* GameFlowSubsystem = UScaredyImpFunctionLibrary::GetGameFlowSubsystem(this);
	if (!IsValid(GameFlowSubsystem)) return;

	GameFlowSubsystem->CompleteGame(this);
}

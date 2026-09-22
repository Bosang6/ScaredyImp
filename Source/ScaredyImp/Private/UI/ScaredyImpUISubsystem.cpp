
#include "UI/ScaredyImpUISubsystem.h"
#include "GameFramework/PlayerController.h"
#include "UI/ScaredyImpUIConfig.h"
#include "UI/ScaredyImpUISettings.h"
#include "UI/HUDWidget.h"
#include "UI/ScaredyImpUIConfig.h"
#include "ScaredyImpCharacter.h"
#include "Enemies/EnemyBase.h"

void UScaredyImpUISubsystem::Initialize(FSubsystemCollectionBase& CollectionBase)
{
	Super::Initialize(CollectionBase);

	// Get Project Settings
	const UScaredyImpUISettings* UISettings = GetDefault<UScaredyImpUISettings>();

	if (IsValid(UISettings))
	{
		UIConfig = UISettings->UIConfig.LoadSynchronous();
	}

	if (!IsValid(UIConfig)) return;

	// The PlayerController may already exist when this subsystem initializes
	// Ensure binding is valid
	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		BindToPlayerController(PlayerController);
	}
}

void UScaredyImpUISubsystem::Deinitialize()
{
	// Stop listening to the current PlayerController
	UnbindFromPlayerController();

	HideGameplayHUD();

	UIConfig = nullptr;

	Super::Deinitialize();
}

void UScaredyImpUISubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	// Stop listening to the previous controller
	UnbindFromPlayerController();

	// Start listening to the new controller
	if (IsValid(NewPlayerController))
	{
		BindToPlayerController(NewPlayerController);
	}
}

APlayerController* UScaredyImpUISubsystem::GetOwningPlayerController() const
{
	const ULocalPlayer* LocalPlayer = GetLocalPlayer();

	if (!IsValid(LocalPlayer)) return nullptr;
	
	// Get the PlayerController belonging to this LocalPlayer in the current World.
	return LocalPlayer->GetPlayerController(GetWorld());
}

void UScaredyImpUISubsystem::SetUIContext(EScaredyImpUIContext NewContext)
{
	if (CurrentUIContext == NewContext) return;

	// Exit old context
	switch (CurrentUIContext)
	{
		case EScaredyImpUIContext::MainMenu:
			// TODO
			// ...
			break;

		case EScaredyImpUIContext::Gameplay:
			HideGameplayHUD();
			break;

		default:
			break;
	}

	CurrentUIContext = NewContext;

	// Enter new context
	switch (CurrentUIContext)
	{
		case EScaredyImpUIContext::MainMenu:
			// TODO
			// ...
			break;

		case EScaredyImpUIContext::Gameplay:
			ShowGameplayHUD();
			break;

		default:
			break;
	}
}

void UScaredyImpUISubsystem::ShowGameplayHUD()
{
	if (IsValid(GameplayHUDWidget)) return;
	if (!IsValid(UIConfig)) return;
	if (!UIConfig->GameplayHUDWidgetClass) return;

	APlayerController* PlayerController = GetOwningPlayerController();
	if (!IsValid(PlayerController)) return;

	// Create the runtime HUD instance using the class configured in DA_UIConfig
	GameplayHUDWidget = CreateWidget<UHUDWidget>(
		PlayerController,
		UIConfig->GameplayHUDWidgetClass
	);

	if (!IsValid(GameplayHUDWidget)) return;

	GameplayHUDWidget->AddToPlayerScreen(0);

	// Ensure that the Character is bound immediately after the HUD is created.
	OnPossessedPawnChanged(
		nullptr,
		PlayerController->GetPawn()
	);
}

void UScaredyImpUISubsystem::HideGameplayHUD()
{
	if (!IsValid(GameplayHUDWidget)) return;

	GameplayHUDWidget->UnbindFromCharacter();
	GameplayHUDWidget->RemoveFromParent();
	GameplayHUDWidget = nullptr;
}

void UScaredyImpUISubsystem::ShowBossStatus(AEnemyBase* Boss)
{
	if (!IsValid(GameplayHUDWidget) || !IsValid(Boss)) return;

	GameplayHUDWidget->ShowBossStatus(Boss);
}

void UScaredyImpUISubsystem::HideBossStatus()
{
	if (!IsValid(GameplayHUDWidget)) return;

	GameplayHUDWidget->HideBossStatus();
}

void UScaredyImpUISubsystem::BindToPlayerController(APlayerController* PlayerController)
{
	if (!IsValid(PlayerController)) return;

	// Keep only a weak reference because the subsystem does not own the Controller
	BoundPlayerController = PlayerController;

	// Listen for Possess / UnPossess changes so the HUD can follow the active Pawn
	PlayerController->OnPossessedPawnChanged.AddUniqueDynamic(
		this,
		&UScaredyImpUISubsystem::OnPossessedPawnChanged
	);
}

void UScaredyImpUISubsystem::UnbindFromPlayerController()
{
	APlayerController* PlayerController = BoundPlayerController.Get();

	if (IsValid(PlayerController))
	{
		PlayerController->OnPossessedPawnChanged.RemoveDynamic(
			this,
			&UScaredyImpUISubsystem::OnPossessedPawnChanged
		);
	}

	BoundPlayerController.Reset();
}

void UScaredyImpUISubsystem::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	if (!IsValid(GameplayHUDWidget)) return;

	GameplayHUDWidget->UnbindFromCharacter();

	AScaredyImpCharacter* PlayerCharacter = Cast<AScaredyImpCharacter>(NewPawn);
	if (!IsValid(PlayerCharacter)) return;

	GameplayHUDWidget->BindToCharacter(PlayerCharacter);
}

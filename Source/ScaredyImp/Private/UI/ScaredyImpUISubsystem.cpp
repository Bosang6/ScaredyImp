
#include "UI/ScaredyImpUISubsystem.h"
#include "GameFramework/PlayerController.h"
#include "UI/ScaredyImpUIConfig.h"
#include "UI/ScaredyImpUISettings.h"
#include "UI/HUDWidget.h"
#include "UI/PopupWidget.h"
#include "ScaredyImpCharacter.h"
#include "Enemies/EnemyBase.h"
#include "Comps/HealthComponent.h"

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
		UpdatePlayerControllerBinding(PlayerController);
	}
}

void UScaredyImpUISubsystem::Deinitialize()
{
	ClearRuntimeUI();

	// Stop listening to the current PlayerController
	UnbindFromPlayerController();

	UIConfig = nullptr;

	Super::Deinitialize();
}

void UScaredyImpUISubsystem::PlayerControllerChanged(APlayerController* NewPlayerController)
{
	Super::PlayerControllerChanged(NewPlayerController);

	// Remove UI belonging to the previous World / PlayerController.
	ClearRuntimeUI();

	if (!IsValid(NewPlayerController)) return;

	UpdatePlayerControllerBinding(NewPlayerController);

	// Rebuild UI for the current context.
	RebuildCurrentUI();
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

	ExitUIContext(CurrentUIContext);

	CurrentUIContext = NewContext;

	EnterUIContext(NewContext);
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

	BindToCharacter(Cast<AScaredyImpCharacter>(PlayerController->GetPawn()));
}

void UScaredyImpUISubsystem::HideGameplayHUD()
{
	if (IsValid(GameplayHUDWidget))
	{
		GameplayHUDWidget->UnbindFromCharacter();
		GameplayHUDWidget->RemoveFromParent();
	}
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

UPopupWidget* UScaredyImpUISubsystem::ShowPopup(EPopupType PopupType)
{
	if (!IsValid(UIConfig)) return nullptr;

	const TSubclassOf<UPopupWidget>* PopupClass = UIConfig->PopupWidgetClasses.Find(PopupType);

	if (!PopupClass || !(*PopupClass)) return nullptr;

	ClosePopup();

	APlayerController* PlayerController = GetOwningPlayerController();
	if (!IsValid(PlayerController)) return nullptr;
	ActivePopupWidget = CreateWidget<UPopupWidget>(PlayerController, *PopupClass);

	if (!IsValid(ActivePopupWidget)) return nullptr;

	ActivePopupWidget->AddToPlayerScreen(10);

	return ActivePopupWidget;
}

void UScaredyImpUISubsystem::ClosePopup()
{
	if (IsValid(ActivePopupWidget))
	{
		ActivePopupWidget->RemoveFromParent();
	}
	ActivePopupWidget = nullptr;
}

void UScaredyImpUISubsystem::OnPlayerDeath()
{
	ShowPopup(EPopupType::GameOver);
}

void UScaredyImpUISubsystem::EnterUIContext(EScaredyImpUIContext Context)
{
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

void UScaredyImpUISubsystem::ExitUIContext(EScaredyImpUIContext Context)
{
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
}

void UScaredyImpUISubsystem::ClearRuntimeUI()
{
	ClosePopup();
	HideGameplayHUD();
}

void UScaredyImpUISubsystem::RebuildCurrentUI()
{
	EnterUIContext(CurrentUIContext);
}

void UScaredyImpUISubsystem::UpdatePlayerControllerBinding(APlayerController* NewPlayerController)
{
	if (BoundPlayerController.Get() == NewPlayerController) return;

	UnbindFromPlayerController();

	if (IsValid(NewPlayerController))
	{
		BindToPlayerController(NewPlayerController);
	}
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

	if (!IsValid(PlayerController))
	{
		BoundPlayerController.Reset();
		return;
	}

	UnbindFromCharacter(Cast<AScaredyImpCharacter>(PlayerController->GetPawn()));

	PlayerController->OnPossessedPawnChanged.RemoveDynamic(this, &UScaredyImpUISubsystem::OnPossessedPawnChanged);

	BoundPlayerController.Reset();
}

void UScaredyImpUISubsystem::BindToCharacter(AScaredyImpCharacter* Character)
{
	if (!IsValid(Character)) return;

	if (UHealthComponent* HealthComponent = Character->GetHealthComponent())
	{
		HealthComponent->OnDeath.AddUniqueDynamic(this, &UScaredyImpUISubsystem::OnPlayerDeath);
	}

	if (IsValid(GameplayHUDWidget))
	{
		GameplayHUDWidget->BindToCharacter(Character);
	}
}

void UScaredyImpUISubsystem::UnbindFromCharacter(AScaredyImpCharacter* Character)
{
	if (!IsValid(Character)) return;

	if (UHealthComponent* HealthComponent = Character->GetHealthComponent())
	{
		HealthComponent->OnDeath.RemoveDynamic(this, &UScaredyImpUISubsystem::OnPlayerDeath);
	}

	if (IsValid(GameplayHUDWidget))
	{
		GameplayHUDWidget->UnbindFromCharacter();
	}
}

void UScaredyImpUISubsystem::OnPossessedPawnChanged(APawn* OldPawn, APawn* NewPawn)
{
	UnbindFromCharacter(Cast<AScaredyImpCharacter>(OldPawn));
	BindToCharacter(Cast<AScaredyImpCharacter>(NewPawn));
}

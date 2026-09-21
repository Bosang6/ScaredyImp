
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScaredyImpUISubsystem.generated.h"

UENUM()
enum class EScaredyImpUIContext : uint8
{
	None,
	MainMenu,
	Gameplay
};

UCLASS()
class SCAREDYIMP_API UScaredyImpUISubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& CollectionBase) override;
	virtual void Deinitialize() override;

	virtual void PlayerControllerChanged(APlayerController* NewPlayerController) override;
	
	APlayerController* GetOwningPlayerController() const;

	void SetUIContext(EScaredyImpUIContext NewContext);

	EScaredyImpUIContext GetUIContext() const { return CurrentUIContext; }

private:
	EScaredyImpUIContext CurrentUIContext = EScaredyImpUIContext::None;
};


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScaredyImpPlayerController.generated.h"

class UInputMappingContext;
class UHUDWidget;

UCLASS(abstract)
class AScaredyImpPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	void RefreshHUDBinding();
	
protected:
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHUDWidget> HUDWidgetClass;

	UPROPERTY()
	TObjectPtr<UHUDWidget> HUDWidget;
};

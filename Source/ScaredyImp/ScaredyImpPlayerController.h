
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ScaredyImpPlayerController.generated.h"

class UInputMappingContext;

UCLASS(abstract)
class AScaredyImpPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
protected:
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;
};

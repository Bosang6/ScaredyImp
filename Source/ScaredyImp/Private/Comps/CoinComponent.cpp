
#include "Comps/CoinComponent.h"
#include "GameFramework/Actor.h"
#include "Comps/HealthComponent.h"
#include "ScaredyImp.h"

UCoinComponent::UCoinComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCoinComponent::AddCoin(int32 Amount)
{
	if (Amount <= 0) return;

	CoinCount += Amount;

	UE_LOG(LogScaredyImp, Log, TEXT("[CoinComponent] CoinCount: %d"), CoinCount);

	if (CoinCount > 0 && CoinCount % CoinPerHeal == 0)
	{
		if (IsValid(HealthComponent) && !HealthComponent->IsFullHealth())
		{
			HealthComponent->Heal(1);
		}
	}
}

void UCoinComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!IsValid(Owner)) return;

	HealthComponent = Owner->GetComponentByClass<UHealthComponent>();
	if (!IsValid(HealthComponent))
	{
		UE_LOG(LogScaredyImp, Error, TEXT("[CoinComponent] not found HealthComponent from %s"), *Owner->GetName());
	}
}

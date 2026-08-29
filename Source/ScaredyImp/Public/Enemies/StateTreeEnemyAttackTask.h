// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tasks/StateTreeAITask.h"
#include "StateTreeEnemyAttackTask.generated.h"

class AEnemyBase;

USTRUCT()
struct FStateTreeEnemyAttackTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<AEnemyBase> Enemy = nullptr;
};

USTRUCT(meta = (DisplayName = "Enemy Attack", Category = "AI|Combat"))
struct SCAREDYIMP_API FStateTreeEnemyAttackTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeEnemyAttackTaskInstanceData;

	FStateTreeEnemyAttackTask()
	{
		bShouldCallTick = true;
	}

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(
		FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition
	) const override;

	virtual EStateTreeRunStatus Tick(
		FStateTreeExecutionContext& Context,
		float DeltaTime
	) const override;
};
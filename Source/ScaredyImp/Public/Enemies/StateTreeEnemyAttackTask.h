// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tasks/StateTreeAITask.h"
#include "StateTreeEnemyAttackTask.generated.h"

USTRUCT()
struct FStateTreeEnemyAttackTaskInstanceData
{
	GENERATED_BODY()
};

USTRUCT(meta = (DisplayName = "Enemy Attack", Category = "AI|Combat"))
struct SCAREDYIMP_API FStateTreeEnemyAttackTask : public FStateTreeAITaskBase
{
	GENERATED_BODY()

	using FInstanceDataType = FStateTreeEnemyAttackTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override
	{
		return FInstanceDataType::StaticStruct();
	}

	virtual EStateTreeRunStatus EnterState(
		FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition
	) const override;
};
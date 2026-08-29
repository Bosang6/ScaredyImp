#include "Enemies/StateTreeEnemyAttackTask.h"
#include "Tasks/StateTreeAITask.h"
#include "StateTreeExecutionContext.h"
#include "ScaredyImp.h"
#include "Enemies/EnemyBase.h"


EStateTreeRunStatus FStateTreeEnemyAttackTask::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition
) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.Enemy))
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.Enemy->Attack();

	UE_LOG(LogScaredyImp, Warning, TEXT("[StateTree] Enemy: %s Attack Task Enterd"), *GetNameSafe(InstanceData.Enemy));

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeEnemyAttackTask::Tick(FStateTreeExecutionContext& Context, float DeltaTime) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!IsValid(InstanceData.Enemy))
	{
		return EStateTreeRunStatus::Failed;
	}

	if (InstanceData.Enemy->IsAttacking())
	{
		return EStateTreeRunStatus::Running;
	}

	UE_LOG(LogScaredyImp, Warning, TEXT("[StateTree] Enemy: %s Attack Task Succeeded"), *GetNameSafe(InstanceData.Enemy));

	return EStateTreeRunStatus::Succeeded;
}

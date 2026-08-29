#include "Enemies/StateTreeEnemyAttackTask.h"

#include "ScaredyImp.h"


EStateTreeRunStatus FStateTreeEnemyAttackTask::EnterState(
	FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition
) const
{
	UE_LOG(LogScaredyImp, Warning, TEXT("[StateTree] Enemy Attack Task Enterd"));

	return EStateTreeRunStatus::Succeeded;
}

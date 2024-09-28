#include "FPS1703_AttackTask.h"
#include "AIController.h"
#include "FPS1703/NPC.h"
//--------------------------------------------------------------------------------------------------------------
UFPS1703_AttackTask::UFPS1703_AttackTask()
{
	NodeName = "Attack";
};
//--------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UFPS1703_AttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto controller = OwnerComp.GetAIOwner();

	if (controller)
	{
		const auto npc = Cast<ANPC>(controller->GetPawn());
		if (npc)
		{
			npc->Attack();
		}
	}
	return EBTNodeResult::Type();
}
//--------------------------------------------------------------------------------------------------------------
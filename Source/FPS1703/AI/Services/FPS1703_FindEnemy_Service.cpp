#include "FPS1703_FindEnemy_Service.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NPC_AIPerceptionComponent.h"

//--------------------------------------------------------------------------------------------------------------
UFPS1703_FindEnemy_Service::UFPS1703_FindEnemy_Service()
{
	NodeName = "Find Enemy";
}
//--------------------------------------------------------------------------------------------------------------
void UFPS1703_FindEnemy_Service::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto blackborad = OwnerComp.GetBlackboardComponent();
	if (blackborad)
	{
		const auto controller = OwnerComp.GetAIOwner();
		const auto perception_component = controller->GetPerceptionComponent();
		NPC_AIPerceptionComponent = Cast<UNPC_AIPerceptionComponent> (perception_component);
		if(perception_component)
		{
			blackborad->SetValueAsObject(Enemy_Actor_Key.SelectedKeyName, NPC_AIPerceptionComponent->GetPlayerCharacter());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
//--------------------------------------------------------------------------------------------------------------

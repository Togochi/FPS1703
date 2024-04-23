#include "FPS1703_RandomNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
//--------------------------------------------------------------------------------------------------------------
UFPS1703_RandomNextLocationTask::UFPS1703_RandomNextLocationTask()
{
	NodeName = "Next Location";
}
//--------------------------------------------------------------------------------------------------------------
EBTNodeResult::Type UFPS1703_RandomNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto controller = OwnerComp.GetAIOwner();
	const auto blackboard = OwnerComp.GetBlackboardComponent();
	if (!controller || !blackboard) return EBTNodeResult::Failed;

	const auto pawn = controller->GetPawn();
	if (!pawn) return EBTNodeResult::Failed;

	const auto nav_system = UNavigationSystemV1::GetCurrent(pawn);
	if (!nav_system) return EBTNodeResult::Failed;

	FNavLocation nav_location;

	auto Location = pawn->GetActorLocation();

	if(!Self_Center)
	{
		auto center_actor = Cast<AActor>(blackboard->GetValueAsObject(Center_Actor_Key.SelectedKeyName));
		if (!center_actor) return EBTNodeResult::Failed;
		Location = center_actor->GetActorLocation();
	}

	const auto found = nav_system->GetRandomReachablePointInRadius(Location, Radius, nav_location);
	if (!found) return EBTNodeResult::Failed;

	blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, nav_location.Location);
	return EBTNodeResult::Succeeded;
}
//--------------------------------------------------------------------------------------------------------------

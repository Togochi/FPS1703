#include "FPS1703_AIController.h"
#include "NPC_AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPS1703/NPC.h"
//--------------------------------------------------------------------------------------------------------------
AFPS1703_AIController::AFPS1703_AIController()
{
	NPC_AIPerceptionComponent = CreateDefaultSubobject<UNPC_AIPerceptionComponent>("NPC_AIPerceptionComponent");
	SetPerceptionComponent(*NPC_AIPerceptionComponent);
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703_AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto npc_parasite = Cast<ANPC_Parasite>(InPawn);

	if (npc_parasite)
	{
		RunBehaviorTree(npc_parasite->BehaviorTreeAsset);
	}
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703_AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto aim_actor = GetFocusOnActor();
	SetFocus(aim_actor);
}
//--------------------------------------------------------------------------------------------------------------
AActor* AFPS1703_AIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
//--------------------------------------------------------------------------------------------------------------


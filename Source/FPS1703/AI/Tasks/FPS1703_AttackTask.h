#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FPS1703_AttackTask.generated.h"
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API UFPS1703_AttackTask : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UFPS1703_AttackTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
//--------------------------------------------------------------------------------------------------------------

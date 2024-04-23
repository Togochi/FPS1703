#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FPS1703_RandomNextLocationTask.generated.h"
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API UFPS1703_RandomNextLocationTask : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFPS1703_RandomNextLocationTask();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") float Radius = 1000.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FBlackboardKeySelector AimLocationKey;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") bool Self_Center = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!Self_Center")) FBlackboardKeySelector Center_Actor_Key;
};
//------------------------------------------------------------------------------------------------------------

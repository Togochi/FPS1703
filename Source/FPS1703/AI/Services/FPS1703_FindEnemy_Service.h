#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FPS1703_FindEnemy_Service.generated.h"

class UNPC_AIPerceptionComponent;
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API UFPS1703_FindEnemy_Service : public UBTService
{
	GENERATED_BODY()
	
public:

	UFPS1703_FindEnemy_Service();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UNPC_AIPerceptionComponent* NPC_AIPerceptionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FBlackboardKeySelector Enemy_Actor_Key;

};
//--------------------------------------------------------------------------------------------------------------

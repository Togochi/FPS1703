#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPS1703_AIController.generated.h"

class UNPC_AIPerceptionComponent;
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AFPS1703_AIController : public AAIController
{
	GENERATED_BODY()

public:
	AFPS1703_AIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Components) UNPC_AIPerceptionComponent* NPC_AIPerceptionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI) FName FocusOnKeyName = "EnemyActor";

private:
	AActor* GetFocusOnActor() const;
};
//--------------------------------------------------------------------------------------------------------------

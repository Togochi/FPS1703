#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "NPC_AIPerceptionComponent.generated.h"
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API UNPC_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetPlayerCharacter() const;
};
//--------------------------------------------------------------------------------------------------------------


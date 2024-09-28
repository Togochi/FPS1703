#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS1703_Menu_PlayerController.generated.h"
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AFPS1703_Menu_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;
	
};
//-------------------------------------------------------------------------------------------------------

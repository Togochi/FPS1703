#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS1703GameMode.generated.h"
//--------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class EGameState : uint8
{
	Waiting_To_Start = 0, 
	InProgress, 
	Pause, 
	GameOver
};
//--------------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState);
//--------------------------------------------------------------------------------------------------------------
UCLASS(minimalapi)
class AFPS1703GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFPS1703GameMode();

	FOnGameStateChanged OnGameStateChanged;
};
//--------------------------------------------------------------------------------------------------------------





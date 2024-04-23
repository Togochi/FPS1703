
#include "FPS1703GameMode.h"
#include "FPS1703Character.h"
#include "UObject/ConstructorHelpers.h"

//--------------------------------------------------------------------------------------------------------------

AFPS1703GameMode::AFPS1703GameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

//--------------------------------------------------------------------------------------------------------------


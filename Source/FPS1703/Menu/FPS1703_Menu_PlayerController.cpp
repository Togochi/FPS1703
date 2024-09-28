#include "FPS1703_Menu_PlayerController.h"
//-------------------------------------------------------------------------------------------------------

void AFPS1703_Menu_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
//-------------------------------------------------------------------------------------------------------
#include "FPS1703_Menu_GameModeBase.h"

//-------------------------------------------------------------------------------------------------------
AFPS1703_Menu_GameModeBase::AFPS1703_Menu_GameModeBase()
{
	PlayerControllerClass = AFPS1703_Menu_PlayerController::StaticClass();
	HUDClass = AFPS1703_Menu_HUD::StaticClass();
}
//-------------------------------------------------------------------------------------------------------
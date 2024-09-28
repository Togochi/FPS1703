#include "Energy_Pickup.h"
#include "FPS1703/FPS1703Character.h"

//-------------------------------------------------------------------------------------------------------

bool AEnergy_Pickup::GivePickupTo(AFPS1703Character* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr)
		return false;

	Energy_Amount = FMath::RandRange(5, 20);
	Character->Set_Energy(Energy_Amount);

	Pickup_Was_Taken();
	return true;
}
//-------------------------------------------------------------------------------------------------------

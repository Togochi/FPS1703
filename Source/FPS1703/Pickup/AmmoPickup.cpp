#include "AmmoPickup.h"
#include "FPS1703/FPS1703Character.h"
#include "FPS1703/HealthComponent.h"
#include "FPS1703/AWeapon.h"
//-------------------------------------------------------------------------------------------------------
DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, Log, All)
//-------------------------------------------------------------------------------------------------------
bool AAmmoPickup::GivePickupTo(AFPS1703Character* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr || !Character->bHasRifle)
		return false;

	if (Character->HealthComponent->IsDead() || !Character->HealthComponent)
		return false;
 
	Character->Current_Weapon->Add_Ammo(Ammo_Amount);
	PickupWasTaken();
	return true;
}
//-------------------------------------------------------------------------------------------------------
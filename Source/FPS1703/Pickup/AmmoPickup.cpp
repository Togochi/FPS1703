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
 
	Ammo_Amount = FMath::RandRange(3, 20);
	Character->Current_Weapon->Add_Ammo(Ammo_Amount);
	Pickup_Was_Taken();
	return true;
}
//-------------------------------------------------------------------------------------------------------
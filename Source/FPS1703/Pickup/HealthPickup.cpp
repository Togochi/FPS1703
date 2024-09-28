#include "HealthPickup.h"
#include "FPS1703/FPS1703Character.h"
#include "FPS1703/HealthComponent.h"
//-------------------------------------------------------------------------------------------------------
DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, Log, All)
//-------------------------------------------------------------------------------------------------------
bool AHealthPickup::GivePickupTo(AFPS1703Character* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr || Character->HealthComponent->IsDead() || !Character->HealthComponent)
		return false;

	if (Character->HealthComponent->Health == Character->HealthComponent->Max_Health)
		return false;

	Health_Amount = FMath::RandRange(5, 20);
	Character->HealthComponent->Set_Health(Character->HealthComponent->Health + Health_Amount);
	Pickup_Was_Taken();
	return true;
}
//-------------------------------------------------------------------------------------------------------

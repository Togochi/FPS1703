#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "AmmoPickup.generated.h"

class UHealthComponent;
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Pickup") bool GivePickupTo(AFPS1703Character* TargetCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0")) int32 Ammo_Amount = 10;
};
//-------------------------------------------------------------------------------------------------------

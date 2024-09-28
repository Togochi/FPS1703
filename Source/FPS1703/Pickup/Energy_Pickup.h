#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "Energy_Pickup.generated.h"

//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AEnergy_Pickup : public ABasePickup
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Pickup") bool GivePickupTo(AFPS1703Character* TargetCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "5.0", ClampMax = "50.0")) int32 Energy_Amount = 10;
	
};
//-------------------------------------------------------------------------------------------------------

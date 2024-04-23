#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealthPickup.generated.h"
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Pickup") bool GivePickupTo(AFPS1703Character* TargetCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "50.0")) int32 Health_Amount = 10;

};
//-------------------------------------------------------------------------------------------------------
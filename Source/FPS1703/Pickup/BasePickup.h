#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class AFPS1703Character;
class USphereComponent;
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ABasePickup();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void Pickup_Was_Taken();

	AFPS1703Character* Character;

	UPROPERTY(VisibleAnywhere, Category = "Pickup") USphereComponent* Collision_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup") float Respawn_Time = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup") float Rotation_Yaw = 1.0f;

private:
	void Respawn();
	void Generate_Rotation_Yaw();
};
//-------------------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS1703/AWeapon.h"
#include "Level_Constructor.generated.h"
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API ALevel_Constructor : public AActor
{
	GENERATED_BODY()
	
public:	
	ALevel_Constructor();

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon") void OnFire(); //temporary function, not used

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon) AWeapon* Weapon; //temporary ptr, not used
};
//--------------------------------------------------------------------------------------------------------------

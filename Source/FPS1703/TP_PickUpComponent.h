#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "FPS1703Character.h"
#include "TP_PickUpComponent.generated.h"

//--------------------------------------------------------------------------------------------------------------

// Declaration of the delegate that will be called when someone picks this up
// The character picking this up is the parameter sent with the notification
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPickUp, AFPS1703Character*, PickUpCharacter);

//-------------------------------------------------------------------------------------------------------

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FPS1703_API UTP_PickUpComponent : public USphereComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category = "Interaction") FOnPickUp OnPickUp; // Delegate to whom anyone can subscribe to receive this event 

	UTP_PickUpComponent();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
//--------------------------------------------------------------------------------------------------------------

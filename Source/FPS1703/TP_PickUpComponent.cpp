#include "TP_PickUpComponent.h"
//--------------------------------------------------------------------------------------------------------------
UTP_PickUpComponent::UTP_PickUpComponent()
{
	SphereRadius = 32.f; // Setup the Sphere Collision
}
//--------------------------------------------------------------------------------------------------------------
void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}
//--------------------------------------------------------------------------------------------------------------
void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFPS1703Character* Character = Cast<AFPS1703Character>(OtherActor); // Checking if it is a First Person Character overlapping

	if (Character != nullptr)
	{
		OnPickUp.Broadcast(Character); // Notify that the actor is being picked up
		OnComponentBeginOverlap.RemoveAll(this); // Unregister from the Overlap Event so it is no longer triggered
	}
}
//--------------------------------------------------------------------------------------------------------------



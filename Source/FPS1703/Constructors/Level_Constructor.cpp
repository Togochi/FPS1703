
#include "Level_Constructor.h"
//--------------------------------------------------------------------------------------------------------------
ALevel_Constructor::ALevel_Constructor()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<AWeapon>(TEXT("Weapon"));

}
//--------------------------------------------------------------------------------------------------------------
void ALevel_Constructor::BeginPlay()
{
	Super::BeginPlay();

}
//--------------------------------------------------------------------------------------------------------------
void ALevel_Constructor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//--------------------------------------------------------------------------------------------------------------


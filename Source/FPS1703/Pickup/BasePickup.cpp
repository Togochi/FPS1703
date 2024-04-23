#include "BasePickup.h"
#include "Components/SphereComponent.h"
//-------------------------------------------------------------------------------------------------------
DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, Log, All)
//-------------------------------------------------------------------------------------------------------
ABasePickup::ABasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

	Collision_Component = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	Collision_Component->InitSphereRadius(50.0f);
	Collision_Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(Collision_Component);
}
//-------------------------------------------------------------------------------------------------------
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	check(Collision_Component);

	Generate_Rotation_Yaw();
}
//-------------------------------------------------------------------------------------------------------
void ABasePickup::PickupWasTaken()
{
	Collision_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(false, true);
	}
	FTimerHandle respawn_timer_handle;
	GetWorldTimerManager().SetTimer(respawn_timer_handle, this, &ABasePickup::Respawn, Respawn_Time);
}
//-------------------------------------------------------------------------------------------------------
void ABasePickup::Respawn()
{
	Generate_Rotation_Yaw();
	Collision_Component->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	if (GetRootComponent())
	{
		GetRootComponent()->SetVisibility(true, true);
	}
}
//-------------------------------------------------------------------------------------------------------
void ABasePickup::Generate_Rotation_Yaw()
{
	const auto direction = FMath::RandBool() ? 1.0f : -1.0f;
	Rotation_Yaw = FMath::RandRange(1.0f, 2.0f) * direction;
}
//-------------------------------------------------------------------------------------------------------
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalRotation(FRotator(0.0f, Rotation_Yaw, 0.0f));
}
//-------------------------------------------------------------------------------------------------------


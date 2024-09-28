#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "Perception/AISense_Damage.h"
//-------------------------------------------------------------------------------------------------------
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//-------------------------------------------------------------------------------------------------------
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Set_Health(Max_Health);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
	{
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeAnyDamage);
	}
}
//-------------------------------------------------------------------------------------------------------
void UHealthComponent::Heal_Update()
{
	Set_Health(Health + Heal_Modifier);

	if (Health==Max_Health && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(Heal_Timer_Handle);
	}
}
//-------------------------------------------------------------------------------------------------------
void UHealthComponent::Set_Health(float new_health)
{
	const auto next_health = FMath::Clamp(new_health, 0.0f, Max_Health);
	const auto health_delta = next_health - Health;

	Health = next_health;
	OnHealthChanged.Broadcast(Health, health_delta);
}
//-------------------------------------------------------------------------------------------------------
void UHealthComponent::ReportDamageEvent(float Damage, AController* InstigatedBy)
{
	if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;

	UAISense_Damage::ReportDamageEvent( GetWorld(), 
													GetOwner(), 
													InstigatedBy->GetPawn(), 
													Damage, 
													InstigatedBy->GetPawn()->GetActorLocation(),
													GetOwner()->GetActorLocation() );
}
//-------------------------------------------------------------------------------------------------------
void UHealthComponent::Play_CameraShake()
{
	if (IsDead()) return;

	const auto player = Cast<APawn>(GetOwner());
	if (!player) return;

	const auto controller = player->GetController<APlayerController>();
	if (!controller || !controller->PlayerCameraManager) return;

	controller->PlayerCameraManager->StartCameraShake(Camera_Shake);
}
//-------------------------------------------------------------------------------------------------------
void UHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
	Set_Health(Health - Damage);
	
	GetWorld()->GetTimerManager().ClearTimer(Heal_Timer_Handle);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (Auto_Heal)
	{
		GetWorld()->GetTimerManager().SetTimer(Heal_Timer_Handle, this, &UHealthComponent::Heal_Update, Heal_Update_Time, true, Heal_Delay);
	}

	Play_CameraShake();
	ReportDamageEvent(Damage, InstigatedBy);
}
//-------------------------------------------------------------------------------------------------------



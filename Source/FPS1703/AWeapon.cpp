#include "AWeapon.h"
#include "Camera/CameraComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/SkeletalMeshSocket.h"
#include "WeaponComponents/FXComponent.h"
#include "Sound/SoundCue.h"
#include "Perception/AISense_Hearing.h"
//-------------------------------------------------------------------------------------------------------
DEFINE_LOG_CATEGORY(LogWeapon);
//-------------------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
	Muzzle_Offset = FVector(100.0f, 0.0f, 10.0f); // Default offset from the character location for projectiles to spawn

	FXComponent = CreateDefaultSubobject<UFXComponent>("FXComponent");
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Attach_To_Character(AFPS1703Character* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr || Character->bHasRifle)
		return;

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->Current_Weapon = this;
	Character->bHasRifle = true;
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Detach()
{
	USceneComponent* root_component = GetRootComponent();

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	//if (UPrimitiveComponent* prim_component = Cast<UPrimitiveComponent>(root_component))
	//{
	//	prim_component->SetSimulatePhysics(true);
	//	prim_component->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	//}
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Add_Ammo(int32 ammo_amount)
{
	if (!Character->bHasRifle) return;
	CurrentAmmo.Bullets += ammo_amount;
	OnAmmoChanged();
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Fire_Start()
{
	if (Character == nullptr || Character->GetController() == nullptr) return;
	
	MakeShot();

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &AWeapon::MakeShot);
	GetWorldTimerManager().SetTimer(ShotTimerHandle, TimerDelegate, TimeBetweenShots, true);
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Fire_End()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Fire_NPC()
{
	if (Fire_Animation_Asset != 0)
		BP_Weapon_Mesh_Component->PlayAnimation(Fire_Animation_Asset, false);
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Play_Fire_Sound()
{
	if (Is_Ammo_Empty()) return;
	
	UGameplayStatics::PlaySoundAtLocation(this, Fire_Sound, Character->GetActorLocation());
	ReportNoiseEvent();
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::ReportNoiseEvent()
{
	if (!Character) return;
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), Character->GetActorLocation(), 1.0f, Character, 6000.f);
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(FXComponent);

	CurrentAmmo = DefaultAmmo;
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::MakeShot()
{
	if (!GetWorld() || Is_Ammo_Empty()) 
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmo_Sound, GetActorLocation());
		Fire_End();
		return;
	}

	OnFire.Broadcast();

	UCameraComponent* character_camera = Character->GetFirstPersonCameraComponent();
	if (!character_camera) return;

	const FVector trace_start = character_camera->GetComponentLocation();
	const FRotator camera_rotation = character_camera->GetComponentRotation();
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector camera_direction = FMath::VRandCone(camera_rotation.Vector(), HalfRad);
	const FVector trace_end = trace_start + camera_direction * TraceMaxDistance;

	//DrawDebugLine(GetWorld(), trace_start, trace_end, FColor::Red, false, 3.0f, 0.0f, 3.0f);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);
	CollisionParams.bTraceComplex = true; // test

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, trace_start, trace_end, ECollisionChannel::ECC_Visibility, CollisionParams);

	Play_Fire_Sound(); 	// Try and play the sound if specified

	if (HitResult.bBlockingHit)
	{
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
		MakeDamage(HitResult);
		FXComponent->PlayImpactFX(HitResult);
	}

	if (Fire_Animation_Montage != 0)
	{
		if (UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance())
			AnimInstance->Montage_Play(Fire_Animation_Montage, 1.0f); // Try and play a firing animation if specified
	}
	Decrease_Ammo();
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto damaged_actor = HitResult.GetActor();
	if (!damaged_actor) return;

	damaged_actor->TakeDamage(Damage_Amount, FDamageEvent(), Character->GetController(), this);
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Decrease_Ammo()
{
	CurrentAmmo.Bullets--;
	OnAmmoChanged();
	Log_Ammo();
}
//-------------------------------------------------------------------------------------------------------
bool AWeapon::Is_Ammo_Empty() const
{
	return CurrentAmmo.Bullets == 0;
}
//-------------------------------------------------------------------------------------------------------
void AWeapon::Log_Ammo()
{
	FString ammo_info = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets);
	UE_LOG(LogWeapon, Display, TEXT("% s"), *ammo_info);
}
//-------------------------------------------------------------------------------------------------------



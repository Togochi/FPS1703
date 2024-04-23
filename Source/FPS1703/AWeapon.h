#pragma once

#include "FPS1703Character.h"
#include "Engine/TimerHandle.h"
#include "Kismet/GameplayStatics.h"
#include "FPS1703Projectile.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "AWeapon.generated.h"

class UFXComponent;
//-------------------------------------------------------------------------------------------------------
DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, Log, All)
//-------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", Meta = (ClampMin = "0.0", ClampMax = "1000.0")) int32 Bullets;
};
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	void Detach();
	void Add_Ammo(int32 ammo_amount);

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapon") void OnAmmoChanged();
	UFUNCTION(BlueprintCallable, Category = "Weapon") FAmmoData Get_Ammo_Data() const { return CurrentAmmo; }
	UFUNCTION(BlueprintCallable, Category = "Weapon") void Attach_To_Character(AFPS1703Character* TargetCharacter);
	UFUNCTION(BlueprintCallable, Category = "Weapon") virtual void Fire_Start();
	UFUNCTION(BlueprintCallable, Category = "Weapon") virtual void Fire_End();
	UFUNCTION(BlueprintCallable, Category = "Weapon") void Fire_NPC();

	UPROPERTY(EditDefaultsOnly, Category = Projectile) TSubclassOf<class AFPS1703Projectile> Projectile_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound_1 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound_2 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound_3 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound_4 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound_5 = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) USoundBase* Fire_Sound_6 = 0;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* Fire_Animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimationAsset* Fire_Animation_Asset = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* Fire_Animation_Montage = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) FVector Muzzle_Offset;

protected:
	virtual void BeginPlay();
	virtual void MakeShot();
	void MakeDamage(const FHitResult& HitResult);
	void Decrease_Ammo();
	bool Is_Ammo_Empty() const;
	void Log_Ammo();
	void Play_Fire_Sound();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon") float Damage_Amount = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components) USkeletalMeshComponent* BP_Weapon_Mesh_Component;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FName MuzzleSocketName = "MuzzleSocket";
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float TraceMaxDistance = 1500.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon") FAmmoData DefaultAmmo{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float TimeBetweenShots = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float BulletSpread = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FAmmoData CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UObject* HUD;
	UPROPERTY(VisibleAnywhere, Category = "VFX") UFXComponent* FXComponent;

private:
	AFPS1703Character* Character;
	FTimerHandle ShotTimerHandle;
};
//-------------------------------------------------------------------------------------------------------

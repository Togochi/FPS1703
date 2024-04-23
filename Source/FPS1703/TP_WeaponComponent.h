#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TP_WeaponComponent.generated.h"

class AFPS1703Character;
//-------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS1703_API UTP_WeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent();


	UFUNCTION(BlueprintCallable, Category = "Weapon") void AttachWeapon(AFPS1703Character* TargetCharacter); // Attaches the actor to a FirstPersonCharacter
	UFUNCTION(BlueprintCallable, Category = "Weapon") void Fire(); // Make the weapon Fire a Projectile 


	UPROPERTY(EditDefaultsOnly, Category=Projectile) TSubclassOf<class AFPS1703Projectile> ProjectileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay) UAnimMontage* FireAnimation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay) FVector MuzzleOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) class UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true")) class UInputAction* FireAction;

protected:

	UFUNCTION() virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	AFPS1703Character* Character; // The Character holding this weapon
};
//-------------------------------------------------------------------------------------------------------


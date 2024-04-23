#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS1703Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
//--------------------------------------------------------------------------------------------------------------
UCLASS(config=Game)
class AFPS1703Projectile : public AActor
{
	GENERATED_BODY()

public:
	AFPS1703Projectile();

	UFUNCTION() void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) USphereComponent* CollisionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true")) UProjectileMovementComponent* ProjectileMovement;
};
//--------------------------------------------------------------------------------------------------------------

#pragma once

#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "FPS1703Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class AWeapon;
class UHealthComponent;
struct FInputActionValue;
//--------------------------------------------------------------------------------------------------------------
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
//--------------------------------------------------------------------------------------------------------------
UCLASS(config=Game)
class AFPS1703Character : public ACharacter
{
	GENERATED_BODY()

public:
	AFPS1703Character();

	virtual void Tick(float DeltaTime) override;

	USkeletalMeshComponent* GetMesh1P() const;
	UCameraComponent* GetFirstPersonCameraComponent() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon) bool bHasRifle; // Bool for AnimBP to switch to another animation set
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon) AWeapon* Current_Weapon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components) UHealthComponent* HealthComponent;
protected:
	virtual void BeginPlay();
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintImplementableEvent) void OnHealthChanged(int32 Health, int32 Health_Delta);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh) USkeletalMeshComponent* Mesh1P;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) TArray<AActor* > Interactable_Actors; // Items that the player can interact with
	UPROPERTY(EditDefaultsOnly, Category = "Damage") FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);
	UPROPERTY(EditDefaultsOnly, Category = "Damage") FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

private:
	void On_Move_Action(const FInputActionValue& Value);
	void On_Look_Action(const FInputActionValue& Value);
	void On_Fire_Action_Start(const FInputActionValue& Value);
	void On_Fire_Action_End(const FInputActionValue& Value);
	void On_Use_Action(const FInputActionValue& Value);

	void OnDeath();

	UFUNCTION() void OnGroundLanded(const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true")) UCameraComponent* FirstPersonCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Look_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Jump_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Move_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Fire_Action_Start;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Fire_Action_End;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true")) UInputAction* Use_Action;
};
//--------------------------------------------------------------------------------------------------------------




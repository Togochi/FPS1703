#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class UCameraShakeBase;
//-------------------------------------------------------------------------------------------------------
DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, int32, int32);
//-------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS1703_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable) bool IsDead() const { return Health <= 0; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health") int32 Health = 0.0f;
protected:
	virtual void BeginPlay() override;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (ClampMin = "0.0", ClampMax = "1000.0")) int32 Max_Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal") bool Auto_Heal = true;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "Auto_Heal")) float Heal_Update_Time = 1.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "Auto_Heal")) float Heal_Delay = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal", meta = (EditCondition = "Auto_Heal")) float Heal_Modifier = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") TSubclassOf<UCameraShakeBase> Camera_Shake;


	friend class AHealthPickup;
private:
	FTimerHandle Heal_Timer_Handle;

	void Heal_Update();
	void Set_Health(float new_health);
	void ReportDamageEvent(float Damage, AController* InstigatedBy);
	UFUNCTION(BlueprintCallable) void Play_CameraShake();

	UFUNCTION() void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

};
//-------------------------------------------------------------------------------------------------------

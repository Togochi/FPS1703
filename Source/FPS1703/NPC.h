#pragma once

#include "AWeapon.h"
#include "GameFramework/Character.h"
#include "Engine/TimerHandle.h"
#include "NPC.generated.h"

class UBehaviorTree;
class UHealthComponent;
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();

	virtual void Tick(float DeltaTime) override;
	virtual void Attack();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Animations) UAnimMontage* Fire_Animation_Montage = 0;

protected:
	virtual void BeginPlay() override;
	void OnDeath();
	void ResetAttackState();

	bool Can_Attack = true;

	UFUNCTION(BlueprintImplementableEvent) void OnHealthChanged(int32 Health, int32 Health_Delta);
	UFUNCTION(BlueprintImplementableEvent) void OnDeath_Effect();
	UFUNCTION(BlueprintImplementableEvent) void OnAttack_Effect();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) AActor* Attack_Target;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components) UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dead) float Life_Span_Time = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack) float Attack_Range = 1000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack) float Attack_Damage = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack) float Attack_Delay = 0.1f;

private:
	void Update_Trace_Direction();

	FTimerHandle Attack_Timer_Handle;

	UPROPERTY(EditAnywhere) FVector Trace_Direction = FVector(1.0f, 0.0f, 0.0f);
};
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API ANPC_Parasite : public ANPC
{
	GENERATED_BODY()

public:
	ANPC_Parasite();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = AI)  UBehaviorTree* BehaviorTreeAsset;
};
//-------------------------------------------------------------------------------------------------------

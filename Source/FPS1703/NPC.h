#pragma once

#include "AWeapon.h"
#include "GameFramework/Character.h"
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
protected:
	virtual void BeginPlay() override;
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent) void OnHealthChanged(int32 Health, int32 Health_Delta);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components) UHealthComponent* HealthComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dead) float Life_Span_Time = 1.0f;
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

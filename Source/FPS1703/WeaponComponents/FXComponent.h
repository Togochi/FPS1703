#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FXComponent.generated.h"

class UNiagaraSystem;
//-------------------------------------------------------------------------------------------------------

UCLASS(ClassGroup = Custom,  meta = (BlueprintSpawnableComponent))
class FPS1703_API UFXComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	UFXComponent();
	void PlayImpactFX(const FHitResult& Hit);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_2;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_3;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_4;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_5;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_6;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_7;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_8;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_9;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX") UNiagaraSystem* Effect_10;


};
//-------------------------------------------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnemyEnvQueryContext.generated.h"
//--------------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API UEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()

public: 
	void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI") FName EnemyActor_KeyName = "EnemyActor";
	
};
//--------------------------------------------------------------------------------------------------------------
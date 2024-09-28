#include "EnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnemyEnvQueryContext.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
//--------------------------------------------------------------------------------------------------------------
void UEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	const auto query_owner = Cast<AActor>(QueryInstance.Owner.Get());
	const auto blackboard = UAIBlueprintHelperLibrary::GetBlackboard(query_owner);
	if (!blackboard) return;

	const auto context_actor = blackboard->GetValueAsObject(EnemyActor_KeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(context_actor));
}
//--------------------------------------------------------------------------------------------------------------
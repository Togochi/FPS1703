#include "NPC_AIPerceptionComponent.h"
#include "AIController.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Hearing.h"
#include "FPS1703/FPS1703Character.h"

//--------------------------------------------------------------------------------------------------------------
AActor* UNPC_AIPerceptionComponent::GetPlayerCharacter() const
{
	TArray<AActor*> percieve_actors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), percieve_actors);
	GetCurrentlyPerceivedActors(UAISense_Hearing::StaticClass(), percieve_actors);
	GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), percieve_actors);
	if (percieve_actors.Num() == 0) return nullptr;
	
	const auto controller = Cast<AAIController>(GetOwner());
	if (!controller) return nullptr;

	const auto pawn = controller->GetPawn();
	if (!pawn) return nullptr;

	AActor* player_character = nullptr;
	for (const auto percive_actor : percieve_actors)
	{
		if (Cast<AFPS1703Character>(percive_actor))
		{
			player_character = percive_actor;
			return player_character;
		}
	}
	return nullptr;
}
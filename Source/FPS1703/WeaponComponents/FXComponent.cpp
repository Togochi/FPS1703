#include "FXComponent.h"
#include "NiagaraFunctionLibrary.h"

//-------------------------------------------------------------------------------------------------------
UFXComponent::UFXComponent()
{
}
//-------------------------------------------------------------------------------------------------------
void UFXComponent::PlayImpactFX(const FHitResult& Hit)
{
	int32 random_number = FMath::RandRange(1, 10);

	UNiagaraSystem* current_effect = 0;

	switch (random_number)
	{
	case 1:
		current_effect = Effect_1;
		break;
	case 2:
		current_effect = Effect_2;
		break;
	case 3:
		current_effect = Effect_3;
		break;
	case 4:
		current_effect = Effect_4;
		break;
	case 5:
		current_effect = Effect_5;
		break;
	case 6:
		current_effect = Effect_6;
		break;
	case 7:
		current_effect = Effect_7;
		break;
	case 8:
		current_effect = Effect_8;
		break;
	case 9:
		current_effect = Effect_9;
		break;
	case 10:
		current_effect = Effect_10;
		break;
	default:
		current_effect = 0;
		break;
	}

	if (current_effect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), current_effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
	}
}
//-------------------------------------------------------------------------------------------------------

#include "NPC.h"
#include "HealthComponent.h"
#include "AI/FPS1703_AIController.h"
#include "GameFramework/CharacterMovementComponent.h"

//ANPC
//-------------------------------------------------------------------------------------------------------
ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}
//-------------------------------------------------------------------------------------------------------
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ANPC::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ANPC::OnHealthChanged);
}
//-------------------------------------------------------------------------------------------------------
void ANPC::OnDeath()
{
	SetLifeSpan(Life_Span_Time);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
}
//-------------------------------------------------------------------------------------------------------
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//ANPC_Parasite
//-------------------------------------------------------------------------------------------------------
ANPC_Parasite::ANPC_Parasite()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = AFPS1703_AIController::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0, 0.0f);
	}
}

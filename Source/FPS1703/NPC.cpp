#include "NPC.h"
#include "HealthComponent.h"
#include "Engine/DamageEvents.h"
#include "AI/FPS1703_AIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"

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

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		Attack_Target = PlayerController->GetPawn();
	}
}
//-------------------------------------------------------------------------------------------------------
void ANPC::OnDeath()
{
	SetLifeSpan(Life_Span_Time);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);

	const auto npc_controller = Cast<AFPS1703_AIController>(Controller);
	if (npc_controller && npc_controller->BrainComponent)
	{
		npc_controller->BrainComponent->Cleanup();
	}

	
	OnDeath_Effect();
}
//-------------------------------------------------------------------------------------------------------
void ANPC::ResetAttackState()
{
	Can_Attack = true;
	Update_Trace_Direction();
	Attack();
}
//-------------------------------------------------------------------------------------------------------
void ANPC::Update_Trace_Direction()
{
	if (Attack_Target)
	{
		FVector npc_location = RootComponent->GetComponentLocation();
		FVector target_location = Attack_Target->GetActorLocation();
		Trace_Direction = (target_location - npc_location).GetSafeNormal();
	}
}
//-------------------------------------------------------------------------------------------------------
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//-------------------------------------------------------------------------------------------------------
void ANPC::Attack()
{
	if (!GetWorld() || HealthComponent->IsDead() || !Can_Attack) 
	{
		return;
	}

	const auto capsule_component = GetCapsuleComponent();
	const FVector trace_start = RootComponent->GetComponentLocation();
	const FVector trace_end = trace_start + Trace_Direction * Attack_Range;


	//DrawDebugLine(GetWorld(), trace_start, trace_end, FColor::Red, false, 3.0f, 0.0f, 3.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);;


	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, trace_start, trace_end, ECollisionChannel::ECC_Visibility, CollisionParams);

	//Play_Attack_Sound(); 	// Try and play the sound if specified

	if (HitResult.bBlockingHit)
	{
		const auto damaged_actor = HitResult.GetActor();
		if (!damaged_actor) return;
		if (Cast<AFPS1703Character>(damaged_actor))
		{
			damaged_actor->TakeDamage(Attack_Damage, FDamageEvent(), GetOwner()->GetInstigatorController(), this);
		}
		//FXComponent->PlayImpactFX(HitResult);
	}

	if (Fire_Animation_Montage != 0)
	{
		if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(Fire_Animation_Montage, 1.0f); // Try and play a firing animation if specified
		}
	}

	Can_Attack = false;

	OnAttack_Effect();
	GetWorld()->GetTimerManager().SetTimer(Attack_Timer_Handle, this, &ANPC::ResetAttackState, Attack_Delay, false);
}
//-------------------------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------------------------
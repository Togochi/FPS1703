#include "FPS1703Character.h"
#include "FPS1703Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "HealthComponent.h"
#include "AWeapon.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);
//--------------------------------------------------------------------------------------------------------------
AFPS1703Character::AFPS1703Character()
{
	PrimaryActorTick.bCanEverTick = true;

	bHasRifle = false; // Character have a rifle at start
	
	GetCapsuleComponent()->InitCapsuleSize(55.0f, 96.0f); 	// Set size for collision capsule

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.0f, 0.0f, -150.f));

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
//--------------------------------------------------------------------------------------------------------------
USkeletalMeshComponent* AFPS1703Character::GetMesh1P() const
{
	return Mesh1P;
}
//--------------------------------------------------------------------------------------------------------------
UCameraComponent* AFPS1703Character::GetFirstPersonCameraComponent() const
{
	return FirstPersonCameraComponent;
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::BeginPlay()
{
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	check(HealthComponent);
	check(GetCharacterMovement());

	HealthComponent->OnDeath.AddUObject(this, &AFPS1703Character::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &AFPS1703Character::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &AFPS1703Character::OnGroundLanded);
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Jump_Action, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(Jump_Action, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(Move_Action, ETriggerEvent::Triggered, this, &AFPS1703Character::On_Move_Action);
		EnhancedInputComponent->BindAction(Look_Action, ETriggerEvent::Triggered, this, &AFPS1703Character::On_Look_Action);
		EnhancedInputComponent->BindAction(Fire_Action_Start, ETriggerEvent::Triggered, this, &AFPS1703Character::On_Fire_Action_Start);
		EnhancedInputComponent->BindAction(Fire_Action_End, ETriggerEvent::Triggered, this, &AFPS1703Character::On_Fire_Action_End);
		EnhancedInputComponent->BindAction(Use_Action, ETriggerEvent::Triggered, this, &AFPS1703Character::On_Use_Action);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::On_Move_Action(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>(); 	// input is a Vector2D

	if (Controller != nullptr)
	{ // add movement 

		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::On_Look_Action(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>(); // input is a Vector2D

	if (Controller != nullptr)
	{// add yaw and pitch input to controller

		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::On_Use_Action(const FInputActionValue& Value)
{
	int i;
	double distance, min_distance;
	AActor *item, *curr_item;
	FVector player_pos, item_pos;

	if (Interactable_Actors.Num() == 0)
		return;

	if (Interactable_Actors.Num() == 1)
	{
		item = Interactable_Actors[0];
		Interactable_Actors.RemoveAt(0);
	}
	else
	{
		player_pos = GetActorLocation();

		for (i = 0; i < Interactable_Actors.Num(); ++i)
		{
			curr_item = Interactable_Actors[i];
			item_pos = curr_item->GetActorLocation();

			distance = FVector::Distance(player_pos, item_pos);

			if ( i == 0 || distance < min_distance)
			{
				min_distance = distance;
				item = curr_item;
			} 
		}
		Interactable_Actors.Remove(item);
	}
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::On_Fire_Action_Start(const FInputActionValue& Value)
{
	if (Current_Weapon != 0)
		Current_Weapon->Fire_Start();
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::On_Fire_Action_End(const FInputActionValue& Value)
{
	if (Current_Weapon != 0)
		Current_Weapon->Fire_End();
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::OnDeath()
{
	UE_LOG(LogTemplateCharacter, Display, TEXT("Player %s is Dead!"), *GetName());
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(1.0f);
	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}
//--------------------------------------------------------------------------------------------------------------
void AFPS1703Character::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;
	UE_LOG(LogTemplateCharacter, Display, TEXT("Fall velocity Z: %f"), FallVelocityZ);

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	UE_LOG(LogTemplateCharacter, Display, TEXT("FinalDamage: %f"), FinalDamage);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}
//--------------------------------------------------------------------------------------------------------------
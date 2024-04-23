#include "TP_WeaponComponent.h"
#include "FPS1703Character.h"
#include "FPS1703Projectile.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//-------------------------------------------------------------------------------------------------------
UTP_WeaponComponent::UTP_WeaponComponent()
{
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f); // Default offset from the character location for projectiles to spawn
}
//-------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::AttachWeapon(AFPS1703Character* TargetCharacter)
{
	Character = TargetCharacter;
	if (Character == nullptr || Character->bHasRifle)
		return;

	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Character->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));

	Character->bHasRifle = true; // switch bHasRifle so the animation blueprint can switch to another animation set

	// Set up action bindings
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->AddMappingContext(FireMappingContext, 1); // Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UTP_WeaponComponent::Fire);
	}
}
//-------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::Fire()
{
	if (Character == nullptr || Character->GetController() == nullptr)
	{
		return;
	}

	// Try and fire a projectile
	if (ProjectileClass != nullptr)
	{
		if (UWorld* World = GetWorld())
		{
			APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
			FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	
			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
			// Spawn the projectile at the muzzle
			World->SpawnActor<AFPS1703Projectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
	
	if (FireSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation()); 	// Try and play the sound if specified
	
	if (FireAnimation != nullptr)
	{ 	
		if (UAnimInstance* AnimInstance = Character->GetMesh1P()->GetAnimInstance())
			AnimInstance->Montage_Play(FireAnimation, 1.0f); // Try and play a firing animation if specified
	}
}
//-------------------------------------------------------------------------------------------------------
void UTP_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Character == nullptr)
		return;

	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
			Subsystem->RemoveMappingContext(FireMappingContext);
	}
}
//-------------------------------------------------------------------------------------------------------

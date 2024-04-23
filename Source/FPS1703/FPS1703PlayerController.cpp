#include "FPS1703PlayerController.h"
#include "EnhancedInputSubsystems.h"
//-------------------------------------------------------------------------------------------------------
void AFPS1703PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 0);

		UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));
	}
}
//-------------------------------------------------------------------------------------------------------
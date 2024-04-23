#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPS1703PlayerController.generated.h"

class UInputMappingContext;
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AFPS1703PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input) UInputMappingContext* InputMappingContext;
};
//-------------------------------------------------------------------------------------------------------

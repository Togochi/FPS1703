#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FPS1703_Menu_HUD.generated.h"
//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API AFPS1703_Menu_HUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI") TSubclassOf<UUserWidget> Menu_Widget_Class;
};
//-------------------------------------------------------------------------------------------------------
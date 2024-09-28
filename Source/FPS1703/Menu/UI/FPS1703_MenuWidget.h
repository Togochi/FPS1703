#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FPS1703_MenuWidget.generated.h"

class USoundCue;
class UButton;

//-------------------------------------------------------------------------------------------------------
UCLASS()
class FPS1703_API UFPS1703_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* Start_Game_Button;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget)) UButton* Quit_Game_Button;
	UPROPERTY(Transient, meta = (BindWidgetAnim)) UWidgetAnimation* Hide_Animation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound") USoundCue* Start_Game_Sound;

private:
	UFUNCTION() void On_Start_Game();
	UFUNCTION() void On_Quit_Game();
	
};
//-------------------------------------------------------------------------------------------------------
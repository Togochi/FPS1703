#include "FPS1703_MenuWidget.h"
#include "Components/Button.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
//-------------------------------------------------------------------------------------------------------
void UFPS1703_MenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (Start_Game_Button)
	{
		Start_Game_Button->OnClicked.AddDynamic(this, &UFPS1703_MenuWidget::On_Start_Game);
	}

	if (Quit_Game_Button)
	{
		Quit_Game_Button->OnClicked.AddDynamic(this, &UFPS1703_MenuWidget::On_Quit_Game);
	}
}
//-------------------------------------------------------------------------------------------------------
void UFPS1703_MenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != Hide_Animation) return;

	const FName startup_level_name = "Map_1";
	UGameplayStatics::OpenLevel(this, startup_level_name);
}
//-------------------------------------------------------------------------------------------------------
void UFPS1703_MenuWidget::On_Start_Game()
{
	PlayAnimation(Hide_Animation);
	UGameplayStatics::PlaySound2D(GetWorld(), Start_Game_Sound);
}
//-------------------------------------------------------------------------------------------------------
void UFPS1703_MenuWidget::On_Quit_Game()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
//-------------------------------------------------------------------------------------------------------
#include "FPS1703_Menu_HUD.h"
#include "Blueprint/UserWidget.h"
//-------------------------------------------------------------------------------------------------------

void AFPS1703_Menu_HUD::BeginPlay()
{
	Super::BeginPlay();

	if (Menu_Widget_Class)
	{
		const auto menu_widget = CreateWidget<UUserWidget>(GetWorld(), Menu_Widget_Class);

		if (menu_widget)
		{
			menu_widget->AddToViewport();
		}
	}
}
//-------------------------------------------------------------------------------------------------------
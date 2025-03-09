//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "SkateClubBaseWidget.h"
#include "WidgetStackBase.h"

//--------------------------------------------------------------------------------------------
void USkateClubBaseWidget::SetParentStack(UWidgetStackBase* MyStackContainer)
{
	StackContainer = MyStackContainer;
}

//--------------------------------------------------------------------------------------------
void USkateClubBaseWidget::NativeOnActivated()
{
	Super::NativeOnActivated();

	if (bAutoRemove)
	{
		if (!GetWorld()->GetTimerManager().IsTimerActive(SelfRemoveTimerHandle)) {
			GetWorld()->GetTimerManager().SetTimer(SelfRemoveTimerHandle, this, &USkateClubBaseWidget::SelfRemove, TimeOnScreen);
		}
	}
}

//--------------------------------------------------------------------------------------------
void USkateClubBaseWidget::SelfRemove()
{
	StackContainer->RemoveWidgetFromScreen(this);
}
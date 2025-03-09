//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "WidgetStackBase.generated.h"

UCLASS()
class SKATECLUB_API UWidgetStackBase : public UCommonActivatableWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UCommonActivatableWidget* PushWidgetToScreen(TSubclassOf <class UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveWidgetFromScreen(class UCommonActivatableWidget* WidgetPointer);
};
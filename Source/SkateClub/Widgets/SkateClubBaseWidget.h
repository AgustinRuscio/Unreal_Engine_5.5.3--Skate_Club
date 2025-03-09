//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "SkateClubBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SKATECLUB_API USkateClubBaseWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()
	
public:	
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	void SetParentStack(class UWidgetStackBase* MyStackContainer);

protected:
	//----------------------------------------------//
	//				PROTECTED VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float TimeOnScreen;

	//----------------------------------------------//
	//				PROTECTED METHODS				//
	//----------------------------------------------//
	virtual void NativeOnActivated() override;

	UFUNCTION()
	virtual void SelfRemove();

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	bool bAutoRemove;

	FTimerHandle SelfRemoveTimerHandle;

	class UWidgetStackBase* StackContainer;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
};
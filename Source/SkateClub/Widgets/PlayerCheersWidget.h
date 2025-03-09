//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "SkateClubBaseWidget.h"
#include "PlayerCheersWidget.generated.h"

/**
 * 
 */
UCLASS()
class SKATECLUB_API UPlayerCheersWidget : public USkateClubBaseWidget
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------//
	//				PUBLIC COMPONENTS				//
	//----------------------------------------------//
	UPROPERTY(BlueprintReadWrite, Category = Components)
	class UTextBlock* Text;

	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	// 
	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	bool GetIsVisible() const;
	void ShowText();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnShow();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnHide();

protected:
	//----------------------------------------------//
	//				PROTECTED VARIABLE				//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PROTECTED METHODS				//
	//----------------------------------------------//
	virtual void SelfRemove();

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TArray<FText> PossibleWords;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	TArray<FLinearColor> PossibleColors;

	FTimerHandle HideTimerHandle;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
};
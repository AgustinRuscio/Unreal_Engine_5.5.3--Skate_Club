//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameSetter.generated.h"

UCLASS()
class SKATECLUB_API AGameSetter : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameSetter();
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	// 
	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditAnywhere, Category = Settings)
	float LevelTime;

	UPROPERTY(EditAnywhere, Category = Settings)
	USoundBase* LevelSFX;
	
	UPROPERTY(EditAnywhere, Category = FeedBack)
	USoundBase* EndGameSFX;

	FTimerHandle WaitTimerHandle;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnEndGame();
};
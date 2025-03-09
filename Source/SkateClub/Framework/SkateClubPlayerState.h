//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SkateClubPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScore, float, NewScore);

UCLASS()
class SKATECLUB_API ASkateClubPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//
	FOnScore OnScore;

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//
	float GetTotalScore() const;

	void AddScore(float ScoreToAdd);

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	float TotalAmount = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float BonificationTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = Settings, meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float BonificationMultiplier = 0.2f;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//
};
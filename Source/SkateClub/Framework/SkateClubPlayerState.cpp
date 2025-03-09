//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "SkateClubPlayerState.h"
#include <Kismet/GameplayStatics.h>

namespace
{
	float LastPointObtain;
}

//--------------------------------------------------------------------------------------------
float ASkateClubPlayerState::GetTotalScore() const
{
	return TotalAmount;
}

//--------------------------------------------------------------------------------------------
void ASkateClubPlayerState::AddScore(float ScoreToAdd)
{
	float diff = UGameplayStatics::GetRealTimeSeconds(GetWorld()) - LastPointObtain;
	LastPointObtain = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	if(diff <= BonificationTime)
		ScoreToAdd += (ScoreToAdd * BonificationMultiplier);

	TotalAmount += ScoreToAdd;

	OnScore.Broadcast(TotalAmount);
}
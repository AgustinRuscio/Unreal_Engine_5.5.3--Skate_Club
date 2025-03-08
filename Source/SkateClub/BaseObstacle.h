//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObstacle.generated.h"

UCLASS()
class SKATECLUB_API ABaseObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseObstacle();

	//----------------------------------------------//
	//				PUBLIC COMPONENTS				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Components)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = Components)
	class UBoxComponent* BoxComp;

	//----------------------------------------------//
	//				PUBLIC VARIABLE					//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PUBLIC METHODS					//
	//----------------------------------------------//

protected:
	//----------------------------------------------//
	//				PROTECTED VARIABLE				//
	//----------------------------------------------//

	//----------------------------------------------//
	//				PROTECTED METHODS				//
	//----------------------------------------------//
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds) override;

private:
	//----------------------------------------------//
	//				PRIVATE VARIABLE				//
	//----------------------------------------------//
	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float ObtaclePoints;

	UPROPERTY(EditDefaultsOnly, Category = Settings)
	float ObstacleCoolDown;

	float UseTimer;

	//----------------------------------------------//
	//				PRIVATE METHODS					//
	//----------------------------------------------//

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
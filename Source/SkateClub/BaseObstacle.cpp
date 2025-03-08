//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "BaseObstacle.h"
#include <Components/BoxComponent.h>
#include "SkateClub/SkateBasePlayer.h"

//--------------------------------------------------------------------------------------------
ABaseObstacle::ABaseObstacle() : ObtaclePoints(10.f), ObstacleCoolDown(3.f), UseTimer(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	BoxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");
	BoxComp->SetupAttachment(Mesh);
}

//--------------------------------------------------------------------------------------------
void ABaseObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ABaseObstacle::BeginOverlap);

	UseTimer = ObstacleCoolDown;
}

//--------------------------------------------------------------------------------------------
void ABaseObstacle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UseTimer += DeltaSeconds;
}

//--------------------------------------------------------------------------------------------
void ABaseObstacle::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASkateBasePlayer* player = Cast<ASkateBasePlayer>(OtherActor);

	if (player && UseTimer >= ObstacleCoolDown)
	{
		player->ObstacleJumped(ObtaclePoints);
		UseTimer = 0;
	}
}
//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "BaseObstacle.h"
#include <Components/BoxComponent.h>
#include "SkateClub/SkateBasePlayer.h"
#include "Framework/SkateClubController.h"

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
	ASkateClubController* Controller = Cast<ASkateClubController>(GetWorld()->GetFirstPlayerController());

	if (player && UseTimer >= ObstacleCoolDown)
	{
		auto PointString = FString::SanitizeFloat(ObtaclePoints);

		player->ObstacleJumped(ObtaclePoints, DisplayFeedBack, ObjectDisplayName, FText::FromString(PointString));

		UseTimer = 0;
	}
}
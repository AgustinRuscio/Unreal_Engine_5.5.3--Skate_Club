//------------------------------------
// Author: Agustin Ruscio
// UE: 5.5.3
//------------------------------------

#include "SkateClubController.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "Framework/Application/SlateApplication.h"
#include "EnhancedInputSubsystems.h"

//--------------------------------------------------------------------------------------------
void ASkateClubController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultMappingContext, 0);

	if (UEnhancedInputComponent* enhantedComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Movement
		enhantedComponent->BindAction(MovePlayerAction, ETriggerEvent::Triggered, this, &ASkateClubController::PlayerMovement);

		// Looking
		enhantedComponent->BindAction(LookAroundAction, ETriggerEvent::Triggered, this, &ASkateClubController::PlayerLookAround);

		// Sprint
		enhantedComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ASkateClubController::StartSprint);
		enhantedComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASkateClubController::StartSprint);

		// Jump
		enhantedComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASkateClubController::PlayerJump);

		// SlowDown
		enhantedComponent->BindAction(SlowDownAction, ETriggerEvent::Triggered, this, &ASkateClubController::PlayerSlowDown);
	}

	SetInputMode(FInputModeGameOnly());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerMovement(const FInputActionValue& value)
{
	OnPlayerMove.Broadcast(value.Get<FVector2D>());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerLookAround(const FInputActionValue& value)
{
	OnPlayerLookAround.Broadcast(value.Get<FVector2D>());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::StartSprint(const FInputActionValue& value)
{
	OnPlayerSprint.Broadcast(value.Get<bool>());
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerJump(const FInputActionValue& value)
{
	OnPlayerJump.Broadcast();
}

//--------------------------------------------------------------------------------------------
void ASkateClubController::PlayerSlowDown(const FInputActionValue& value)
{
	OnPlayerSlowDown.Broadcast();
}
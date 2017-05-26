// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ThisTank = GetPawn();
	
	if (ensure(PlayerTank && ThisTank))
	{
		//move towards player
		MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius value

		auto AimingComponent = ThisTank->FindComponentByClass<UTankAimingComponent>();
		//Aim towards player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		if (AimingComponent->GetFiringState() == AimStates::Ready)
		AimingComponent->Fire();
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto myAITank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (myAITank) { UE_LOG(LogTemp, Warning, TEXT("Found AI Tank: %s"), *(myAITank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Found!")); }

	if (PlayerTank) { UE_LOG(LogTemp, Warning, TEXT("Found Player Tank: %s"), *(PlayerTank->GetName())); }
	else { UE_LOG(LogTemp, Warning, TEXT("Player Tank Not Found!")); }
}
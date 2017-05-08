// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

ATank* ATankAIController::GetAIControlledTank() const {

	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	///UE_LOG(LogTemp, Warning, TEXT("We are ticking!"));
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		/// TODO move towards player

		//Aim towards player
		GetAIControlledTank()->AimAt(PlayerTank->GetActorLocation());
	}
}


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* myAITank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = GetPlayerTank();

	if (myAITank) {
		UE_LOG(LogTemp, Warning, TEXT("Found AI Tank: %s"), *(myAITank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI Tank Not Found!"));
	}

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank: %s"), *(PlayerTank->GetName()));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank Not Found!"));
	}
}
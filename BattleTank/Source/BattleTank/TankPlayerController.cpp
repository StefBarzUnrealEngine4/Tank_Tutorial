// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("We are ticking!"));
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	
	if (!GetPawn()) { return; } // if not possessing or not ready
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	
	if (ensure(AimingComponent)) {
		FVector HitLocation; //Out parameter
		if (GetSightRayHitLocation(HitLocation)) { AimingComponent->AimAt(HitLocation); }
	}
}

// Get world location of linetrace through crosshair, return true if hittin landscape
bool ATankPlayerController::GetSightRayHitLocation(OUT FVector &OutHitLocation) const {
	// Find screen pixel coords
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	float ScreenXLocation = (ViewportSizeX * this->CrossHairXLocation);
	float ScreenYLocation = (ViewportSizeY * this->CrossHairYLocation);
	FVector2D ScreenLocation = FVector2D(ScreenXLocation, ScreenYLocation);
	
	// "De-Project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		/// Line-trace along that look direction, see what we hit (up to a max range)
		return GetLookVectorHitLocation(LookDirection, OUT OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const {
	FVector CameraWorldLocation; //discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

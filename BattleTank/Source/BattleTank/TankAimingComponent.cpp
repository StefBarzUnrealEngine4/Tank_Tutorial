// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	//TODO Should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FString TankName = GetOwner()->GetName();
	auto Time = GetWorld()->GetTimeSeconds();
	///FString BarrelLocation = Barrel->GetComponentLocation().ToString();
	///UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *TankName, *HitLocation.ToString(), *BarrelLocation);

	if (!Barrel) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	///calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))	// required default params due to bug in UE4
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		///UE_LOG(LogTemp, Warning, TEXT("%f Aim Direction: %s"), Time, *AimDirection.ToString());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("%f No Aim Direction"), Time);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); ///roll pitch yaw rotator struct
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	//work out difference between current barrel rotation and aim direction
	auto TurretRotator = Turret->GetForwardVector().Rotation(); ///roll pitch yaw rotator struct
	auto AimAtRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAtRotator - TurretRotator;

	Turret->ChangeAzimuth(DeltaRotator.Yaw);
}


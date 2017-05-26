// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Init(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FString TankName = GetOwner()->GetName();
	auto Time = GetWorld()->GetTimeSeconds();
	///FString BarrelLocation = Barrel->GetComponentLocation().ToString();
	///UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *TankName, *HitLocation.ToString(), *BarrelLocation);

	if (!ensure(Barrel)) { return; }
	
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	///calculate OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace))	// required default params due to bug in UE4
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
		///UE_LOG(LogTemp, Warning, TEXT("%f Aim Direction: %s"), Time, *AimDirection.ToString());
	}
	else {
		///UE_LOG(LogTemp, Warning, TEXT("%f No Aim Direction"), Time);
	}
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (GetAmmoCount() <= 0) {
		AimStatus = AimStates::OutofAmmo;
	}
	else if ((GetWorld()->TimeSeconds - LastFireTime) < ReloadTimeInSeconds) {
		AimStatus = AimStates::Reloading;
	}
	else if (IsBarrelMoving()) {
		AimStatus = AimStates::Aiming;
	}
	else {
		AimStatus = AimStates::Ready;
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !(BarrelForward.Equals(AimDirection, 0.01));
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	//spawn projectile at Projectile socket location
	auto MyProjectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

		MyProjectile->LaunchProjectile(2000.0f); // TODO fix this
		AimStatus = AimStates::Reloading;
		AmmoCount--;
		LastFireTime = GetWorld()->TimeSeconds;
}

int32 UTankAimingComponent::GetAmmoCount() const { return AmmoCount; }

//Get the firing state of this tank
AimStates UTankAimingComponent::GetFiringState() const { return this->AimStatus; }

void UTankAimingComponent::MoveBarrelTowards(FVector AimDir)
{
	if (!ensure(Barrel)) { return; }
	//work out difference between current barrel elevation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation(); ///roll pitch yaw rotator struct
	auto AimAtRotator = AimDir.Rotation();
	auto DeltaRotator = AimAtRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDir)
{
	if (!ensure(Turret)) { return; }
	//work out difference between current turret rotation and aim direction
	auto TurretRotator = Turret->GetForwardVector().Rotation(); ///roll pitch yaw rotator struct
	auto AimAtRotator = AimDir.Rotation();
	auto DeltaRotator = AimAtRotator - TurretRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180) {
		Turret->ChangeAzimuth(DeltaRotator.Yaw);
	}
	else {
		Turret->ChangeAzimuth(-DeltaRotator.Yaw);
	}
}
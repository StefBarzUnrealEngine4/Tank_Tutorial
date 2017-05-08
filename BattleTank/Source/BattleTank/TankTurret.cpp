// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::ChangeAzimuth(float RelativeSpeed)
{
	auto ClampedSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
	//move the turret the right amount this frame
	auto AzimuthChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewAzimuth = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0, NewAzimuth, 0));
};
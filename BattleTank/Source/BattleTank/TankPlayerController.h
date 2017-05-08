// Copyright Steve Barnes 2017 

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // make sure this is last include

//forward declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void Tick(float DeltaTime) override;
	void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; ///10km

	//Start the tank moving barrel so that a shot would hit where crosshair intersects world
	void AimTowardsCrosshair();

private:
	bool GetSightRayHitLocation(OUT FVector &outVec) const;
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
};

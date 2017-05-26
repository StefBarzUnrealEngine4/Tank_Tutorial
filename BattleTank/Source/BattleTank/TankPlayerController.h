// Copyright Steve Barnes 2017 

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // make sure this is last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

public:
	virtual void Tick(float DeltaTime) override;
	void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000; ///10km

	//Start the tank moving barrel so that a shot would hit where crosshair intersects world
	void AimTowardsCrosshair();

private:
	bool GetSightRayHitLocation(OUT FVector &outVec) const;
	bool GetLookDirection(FVector2D ScreenLocation, OUT FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const;
};

// Copyright Steve Barnes 2017 

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision"))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0.0f;
};

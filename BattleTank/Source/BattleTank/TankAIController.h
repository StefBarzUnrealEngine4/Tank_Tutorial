// Copyright Steve Barnes 2017 

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h" // make sure this is last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	//How close can the AI tank get to the player
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 10.0f; //TODO this is not working
};

// Copyright Steve Barnes 2017 

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h" // make sure this is last include

///forward declarations
class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	void BeginPlay() override;
	ATank* GetAIControlledTank() const;
	ATank* GetPlayerTank() const;
	virtual void Tick(float DeltaTime) override;
};

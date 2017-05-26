// Copyright Steve Barnes 2017 

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming states
UENUM()
enum class AimStates : uint8
{
	Reloading,
	Aiming,
	Ready,
	OutofAmmo
};

//forward declaraion
class UTankBarrel;
class UTankTurret;

// Holds barrel's properties and elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AimAt(FVector WorldSpaceAim);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Init(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Actions")
	int32 GetAmmoCount() const;

	AimStates GetFiringState() const;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	UClass* ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 40000.0f; /// TODO - find sensible default value

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 AmmoCount = 3;

	double LastFireTime = 0.0f;
	FVector AimDirection = FVector::ZeroVector;
	bool IsBarrelMoving();



protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	AimStates AimStatus = AimStates::Aiming;
};
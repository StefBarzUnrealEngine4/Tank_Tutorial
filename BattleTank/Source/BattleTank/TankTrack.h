// Copyright Steve Barnes 2017 

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Used to set max driving force and apply forces to move tank
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

private:
	UTankTrack();
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	void ApplySidewaysForce();
	void DriveTrack();
	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDrivingForce = 12000000.0f; //TODO sensible value?
	
	float SlippageSpeed = 0.0f;
	float TankMass = 0.0f;
	float CurrentThrottle = 0.0f;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};

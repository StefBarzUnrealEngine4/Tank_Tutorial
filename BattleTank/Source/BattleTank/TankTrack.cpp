// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	///UE_LOG(LogTemp, Warning, TEXT("Track is ticking"));
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("Tracks hitting ground!"));
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0.0f;
}

void UTankTrack::ApplySidewaysForce() {
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto TankStaticMeshComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	TankMass = TankStaticMeshComponent->GetMass();
	SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	FVector CorrectionAcceleration = -((SlippageSpeed / DeltaTime) * GetRightVector());
	//F = m * a
	FVector CorrectionForce = ((TankMass * CorrectionAcceleration) / 2); // 2 tracks
	TankStaticMeshComponent->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	///auto Name = GetName();
	///UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack() {
	auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(this->GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
	FVector IntendedMoveDirection = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector();
	
	IntendTurnRight(FVector::CrossProduct(TankForward, IntendedMoveDirection).Z); // turn throw is z of cross product
	IntendMoveForward(FVector::DotProduct(TankForward, IntendedMoveDirection)); //forward throw is dot product
	
	FString Name = GetOwner()->GetName();

	///UE_LOG(LogTemp, Warning, TEXT("%s, %s"), *Name, *(IntendedMoveDirection.ToString()));
}

// Copyright Steve Barnes 2017 

#include "BattleTank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ProjectileCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("My Collision Mesh"));
	SetRootComponent(ProjectileCollisionMesh);

	ProjectileCollisionMesh->SetNotifyRigidBodyCollision(true);
	ProjectileCollisionMesh->SetVisibility(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("My Particles"));

	MyProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("My Projectile Moving Component"));
	MyProjectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float Speed) {
	UE_LOG(LogTemp, Warning, TEXT("Projetile Launched at %f"), Speed);
	MyProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MyProjectileMovementComponent->Activate();
}

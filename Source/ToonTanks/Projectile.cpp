// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = 1300.f;
	ProjectileMovementComponent -> MaxSpeed = 3000.f;

	ProjectileTrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail Particle"));
	ProjectileTrailParticle-> SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, & AProjectile::OnHit);
	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherHitComponent, FVector NormalImpulse, const FHitResult& HitResult)
{
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) 
	{
		Destroy();
		return;
	}

	auto MyOnwerInstigator = MyOwner-> GetInstigatorController();
	auto DamageType = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOnwerInstigator, this, DamageType);
	
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation(), GetActorRotation());
	}
	if(ExplodeSound)
		UGameplayStatics::PlaySoundAtLocation(this,ExplodeSound, GetActorLocation());
	
	if(HitCameraShake)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShake);
	Destroy();
}


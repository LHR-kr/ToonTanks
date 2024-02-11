// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	float Damage = 50.f;

	UPROPERTY(EditAnywhere,Category = "Combat")
	class UParticleSystem* HitParticle;
	
	UPROPERTY(VisibleAnywhere, Category = "Combat")
	class UParticleSystemComponent* ProjectileTrailParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* ExplodeSound;

	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	//블루프린트라서  TSubClass를 하나 만들어준다.
	TSubclassOf<class UCameraShakeBase> HitCameraShake;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherHitComponent, FVector NormalImpulse, const FHitResult& HitResult);
};

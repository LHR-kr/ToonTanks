// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//생성자는 에디터에서 생성되기만 해도 실행된다.
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	BaseMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh -> SetupAttachment(CapsuleComponent);
	
	TurretMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("Projectile Spawn Point");
	ProjectileSpawnPoint ->SetupAttachment(TurretMesh);
}


void ABasePawn::RotateTurret(FVector TargetWorldLocationVector)
{
	FVector RotateVector = TargetWorldLocationVector - TurretMesh->GetComponentLocation();
	FRotator Rotator (0.f,RotateVector.Rotation().Yaw,0.f);

	//위의 RotateVector를 계산하기 위한 위치 벡터가 월드 좌표계이므로 World Rotation을 호출한다.
	//터렛이 휙휙 돌아가는 것을 방지하기 위해 보간 함수를 사용한다.
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),Rotator,UGameplayStatics::GetWorldDeltaSeconds(this),10.f));

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePawn::Fire()
{
	UE_LOG(LogTemp, Display, TEXT("fire"));
}
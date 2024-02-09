// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm -> SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera -> SetupAttachment(SpringArm);
}
void ATank :: BeginPlay()
{
    Super::BeginPlay();
    PlayerController = Cast<APlayerController>(GetController());
}

void ATank::HandleDesruction()
{
	Super::HandleDesruction();
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// 축 매핑에 함수를 바인딩
void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent); 
    PlayerInputComponent -> BindAxis(TEXT("MoveForward"),this, & ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn"),this, & ATank::Rotate);
    PlayerInputComponent -> BindAction(TEXT("Fire"), IE_Pressed,this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(PlayerController)
    {
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility,false,HitResult);

        RotateTurret(HitResult.ImpactPoint);
    }
    
}

void ATank::Move(float Value)
{
    FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::Rotate(float Value)
{
    FRotator DeltaRotator = FRotator::ZeroRotator;
    DeltaRotator.Yaw = Value * RotateRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    //bSweep으로 이동한 후 충돌 감지 기능 활성화
    AddActorLocalRotation(DeltaRotator,true);
}

APlayerController* ATank:: GetPlayerController() const
{
    return this->PlayerController;
}

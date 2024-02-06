// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    
    //탱크 사이의 거리를 구하고
    float DistanceTargetTank = FVector::Dist(GetActorLocation(), TargetTank->GetActorLocation());
    //거리가 유효 사거리 안이면
    //터렛을 회전
    if(CheckTargetInFireRange())
    {
        RotateTurret(TargetTank->GetActorLocation());
    }
        
    
    
    
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    TargetTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    GetWorldTimerManager().SetTimer(FireRateTimerHandle,this, & ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
 

    if(CheckTargetInFireRange())
    {
        Fire();
    }
        
    
}

bool ATower::CheckTargetInFireRange()
{
    if(!TargetTank) return false;
    return FVector::Dist(GetActorLocation(), TargetTank->GetActorLocation()) <= FireRange;
}
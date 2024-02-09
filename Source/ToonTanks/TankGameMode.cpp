// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATankGameMode::ActorDied(AActor* DiedActor)
{
    if(DiedActor == Tank)
    {
        Tank->HandleDesruction();
        if(Tank->GetPlayerController())
        {
            Tank->DisableInput(Tank->GetPlayerController());
            Tank->GetPlayerController()-> bShowMouseCursor = false;
        }
    }
    else if( ATower* DestroyedActor = Cast<ATower>(DiedActor))
    {
        DestroyedActor -> HandleDesruction();
    }
}

void ATankGameMode::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}
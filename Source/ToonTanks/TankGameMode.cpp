// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ATankGameMode::ActorDied(AActor* DiedActor)
{
    if(DiedActor == Tank)
    {
        Tank->HandleDesruction();
        if(ToonTankPlayerController)
        {
            ToonTankPlayerController->SetPlayerEnabledState(false);
        }
        FinishGame(false);
    }
    else if( ATower* DestroyedActor = Cast<ATower>(DiedActor))
    {
        DestroyedActor -> HandleDesruction();
        --TowerCount;
        if(TowerCount == 0)
            FinishGame(true);
    }
}

void ATankGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
}

void ATankGameMode::HandleGameStart()
{
    TowerCount = GetTowerCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
    ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this,0));
    StartGame();
    if(ToonTankPlayerController)
    {
        ToonTankPlayerController->SetPlayerEnabledState(false);

        FTimerHandle StartTimerHandle;
        FTimerDelegate PlayerEnableInputTimeDelegate = FTimerDelegate::CreateUObject(ToonTankPlayerController, &AToonTankPlayerController::SetPlayerEnabledState,true);

        // StartDelay만큼의 시간이 흐른 뒤에 PlayerEnableInputTimeDelegate가 호출된다.
        GetWorldTimerManager().SetTimer(StartTimerHandle, PlayerEnableInputTimeDelegate, StartDelay, false);
    }
}

int32 ATankGameMode:: GetTowerCount()
{
    TArray<AActor*> TowerActors;
    //UClASS를 생성하기 위해서 StaticClass() 호출
    UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),TowerActors);

    return TowerActors.Num();
}
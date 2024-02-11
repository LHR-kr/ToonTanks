// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ActorDied(AActor* DiedActor);
private:
	class ATank* Tank;
	class AToonTankPlayerController* ToonTankPlayerController;

	float StartDelay = 3.f;

	void HandleGameStart();

	int32 TowerCount;

	int32 GetTowerCount();

protected:
	void BeginPlay();

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	UFUNCTION(BlueprintImplementableEvent)
	void FinishGame(bool bIsWin);
};


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 400.0f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotateRate = 45.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetPlayerController() const;
	void HandleDesruction();

	bool GetIsAlive() const;

private:
	void Move(float Value);
	void Rotate(float Value);
	APlayerController* PlayerController;

	bool IsAlive;

	UPROPERTY(EditDefaultsOnly,Category = "Combat")
	//블루프린트라서  TSubClass를 하나 만들어준다.
	TSubclassOf<class UCameraShakeBase> DieCameraShake;

};

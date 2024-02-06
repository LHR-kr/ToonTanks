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
private:
	void Move(float Value);
	void Rotate(float Value);
	APlayerController* PlayerControllerRef;
};

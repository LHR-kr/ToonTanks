// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;

	// OnTakeAnyDamage는 AActor의 멤버 함수이다.
	// 컴포넌트에서 호출하기 때문에 GetOWner()를 호출하여 액터에 접근한 후 호출한다.
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamage);

	TankGameMode = Cast<ATankGameMode>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	if(Damage<= 0.f) return;

	HP-=Damage;
	if(HP<=0.f && TankGameMode)
	{
		TankGameMode->ActorDied(DamagedActor);
	}
}
// Shoot Them Up Game, All Rights Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY_STATIC(MyLogHealthComponent, All, All);


USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* ComponentOwner = GetOwner();
	ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
}

void USTUHealthComponent::OnTakeAnyDamage(
	AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	//UE_LOG(MyLogCharacter, Display, TEXT("Damage %f"), Damage);
	Health -= Damage;
	UE_LOG(MyLogHealthComponent, Warning, TEXT("Damage: %f"), Damage);
}
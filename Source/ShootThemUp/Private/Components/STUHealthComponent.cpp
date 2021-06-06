// Shoot Them Up Game, All Rights Reserved.


#include "Components/STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/STUFireDamageType.h"
#include "Dev/STUIceDamageType.h"

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
	Health -= Damage;
	UE_LOG(MyLogHealthComponent, Warning, TEXT("Damage: %f"), Damage);

	if (DamageType->IsA<USTUFireDamageType>())
	{
		UE_LOG(MyLogHealthComponent, Warning, TEXT("So hooooot!"));
	}
	else if (DamageType->IsA<USTUIceDamageType>())
	{
		UE_LOG(MyLogHealthComponent, Warning, TEXT("So cooooold!"));
	}
}
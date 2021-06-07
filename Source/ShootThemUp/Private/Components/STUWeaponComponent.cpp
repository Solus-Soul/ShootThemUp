// Shoot Them Up Game, All Rights Reserved.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);

	FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, false};
	CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
	CurrentWeapon->SetOwner(Character);
}

void USTUWeaponComponent::StartFire() 
{
	if (!CurrentWeapon) return;
	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	if (!CurrentWeapon)
		return;
	CurrentWeapon->StopFire();
}

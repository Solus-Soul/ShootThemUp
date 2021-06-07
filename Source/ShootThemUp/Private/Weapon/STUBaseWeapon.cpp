// Shoot Them Up Game, All Rights Reserved.

#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
	

DEFINE_LOG_CATEGORY_STATIC(MyLogBaseWeapon, All, All);


ASTUBaseWeapon::ASTUBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(WeaponMesh);

}

void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(WeaponMesh);
	
}

void ASTUBaseWeapon::StartFire() 
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTUBaseWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTUBaseWeapon::StopFire() 
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTUBaseWeapon::MakeShot() 
{
	FVector TraceStart, TraceEnd;
	GetTraceDate(TraceStart, TraceEnd);

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);


	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}

APlayerController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());

	return Player->GetController<APlayerController>(); 
}

void ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const 
{
	const auto Controller = GetPlayerController();
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
}

FVector ASTUBaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

void ASTUBaseWeapon::GetTraceDate(FVector& TraceStart, FVector& TraceEnd) const 
{
	FVector ViewLocation;
	FRotator ViewRotation;
	GetPlayerViewPoint(ViewLocation, ViewRotation);

	TraceStart = ViewLocation;
	const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
}

void ASTUBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, FVector& TraceEnd) 
{
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ASTUBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamageActor = HitResult.GetActor();
	if (!DamageActor) return;

	DamageActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
// Shoot Them Up Game, All Rights Reserved.

#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

void ASTULauncherWeapon::StartFire()
{
	MakeShot();
}

void ASTULauncherWeapon::StopFire() {}

void ASTULauncherWeapon::MakeShot()
{
	if (!GetWorld()) return;

	if (IsAmmoEmpty())
	{
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
		return;
	}

	FVector TraceStart, TraceEnd;
	GetTraceDate(TraceStart, TraceEnd);

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
	const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

	const FTransform SpawnTransform{FRotator::ZeroRotator, GetMuzzleWorldLocation()};
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);

	Projectile->SetShotDirection(Direction);
	Projectile->SetOwner(GetOwner());
	Projectile->FinishSpawning(SpawnTransform);

	DecreaseAmmo();
	SpawnMuzzleFX();
	UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}
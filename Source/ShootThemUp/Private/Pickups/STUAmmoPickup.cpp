// Shoot Them Up Game, All Rights Reserved.


#include "Pickups/STUAmmoPickup.h"

DEFINE_LOG_CATEGORY_STATIC(MyLogAmmoPickup, All, All)

bool ASTUAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(MyLogAmmoPickup, Display, TEXT("Ammo Was Taken!"));
	return true;
}
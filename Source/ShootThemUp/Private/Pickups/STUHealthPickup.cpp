// Shoot Them Up Game, All Rights Reserved.


#include "Pickups/STUHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(MyLogHealthPickup, All, All)


bool ASTUHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
	UE_LOG(MyLogHealthPickup, Display, TEXT("Health Was Taken!"));
	return true;
}
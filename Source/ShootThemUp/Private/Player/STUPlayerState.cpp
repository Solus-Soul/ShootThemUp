// Shoot Them Up Game, All Rights Reserved.


#include "Player/STUPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(MyLogPlayerState, All, All);

void ASTUPlayerState::LogInfo()
{
	UE_LOG(MyLogPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, KillsNum, DeathsNum);
}

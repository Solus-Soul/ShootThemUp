// Shoot Them Up Game, All Rights Reserved.

#include "UI/STUPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTUPlayerStatRowWidget::SetPLayerName(const FText& Text)
{
	if (!PlayerNameTextBlock)
	{
		return;
	}
	PlayerNameTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetKills(const FText& Text)
{
	if (!PlayerNameTextBlock)
	{
		return;
	}
	KillsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetDeaths(const FText& Text)
{
	if (!PlayerNameTextBlock)
	{
		return;
	}
	DeathsTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetTeams(const FText& Text)
{
	if (!PlayerNameTextBlock)
	{
		return;
	}
	TeamTextBlock->SetText(Text);
}

void USTUPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if (!PlayerNameTextBlock)
	{
		return;
	}
	PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if (!TeamImage)
	{
		return;
	}
	TeamImage->SetColorAndOpacity(Color);
}

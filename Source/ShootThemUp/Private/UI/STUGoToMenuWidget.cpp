// Shoot Them Up Game, All Rights Reserved.

#include "UI/STUGoToMenuWidget.h"
#include "Components/Button.h"
#include "STUGameInstance.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(MyLogGoToMenuWidget, All, All);

void USTUGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &USTUGoToMenuWidget::OnGoToMenu);
	}
}

void USTUGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld())
	{
		return;
	}

	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
	if (!STUGameInstance)
	{
		return;
	}

	if (STUGameInstance->GetStartupMenuName().IsNone())
	{
		UE_LOG(MyLogGoToMenuWidget, Error, TEXT("Menu Level name is none"))
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupMenuName());
}

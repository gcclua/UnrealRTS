#include "HUDPanelBuildings.h"

#include "TowerDefense/Core/PlayerVitalsBase.h"

void UHUDPanelBuildingsBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (UpgradeButton != nullptr)
		UpgradeButton->OnClicked.AddDynamic(this, &UHUDPanelBuildingsBase::OnUpgradeButtonClicked);
}

void UHUDPanelBuildingsBase::PopulateData(TScriptInterface<IBuilding> building)
{
	if (building == nullptr)
		return;
	
	currentBuilding = building;
	FillFields();
}

void UHUDPanelBuildingsBase::OnUpgradeButtonClicked()
{
	const int currentLevel = currentBuilding->CurrentLevel();
	const int maxLevel = currentBuilding->MaxLevel();

	APlayerVitalsBase* playerVitals = APlayerVitalsBase::GetInstance();
	if (playerVitals == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UHUDPanelBuildingsBase: PlayerVitals is null"));
		return;
	}

	int currentMoney = playerVitals->GetMoney();
	const int nextCostMoney = currentBuilding->NextCostMoney();
	if (currentLevel >= maxLevel || currentMoney < nextCostMoney)
		return;

	currentMoney -= nextCostMoney;
	playerVitals->SetMoney(currentMoney);
	currentBuilding->UpgradeToLevel(currentLevel + 1);

	FillFields();
}

void UHUDPanelBuildingsBase::FillFields()
{
	if (currentBuilding == nullptr)
		return;
	
	HeaderText->SetText(FText::FromString(currentBuilding->HeaderString()));

	const int currentLevel = currentBuilding->CurrentLevel();
	const int maxLevel = currentBuilding->MaxLevel();
	
	const FString levelTextString = FString::Printf(TEXT("Level: %d, Max: %d"), currentLevel, maxLevel);
	LevelText->SetText(FText::FromString(levelTextString));

	if (currentLevel >= maxLevel)
	{
		NextCostText->SetText(FText::FromString(""));	
	}
	else
	{
		const FString nextCostString = FString::Printf(TEXT("Cost: %d"), currentBuilding->NextCostMoney());
		NextCostText->SetText(FText::FromString(nextCostString));	
	}
}

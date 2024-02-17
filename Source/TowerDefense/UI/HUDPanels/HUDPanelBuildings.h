#pragma once

#include "HUDPanelBase.h"
#include "IHUDPanelBuildings.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HUDPanelBuildings.generated.h"

UCLASS(ABSTRACT)
class UHUDPanelBuildingsBase : public UHUDPanelBase, public IHUDPanelBuildingsInterface
{
	GENERATED_BODY()

protected:
	TScriptInterface<IBuilding> currentBuilding;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnUpgradeButtonClicked();

	void FillFields();
	
public:
	UPROPERTY(EditAnywhere, Category = "Buildings Panel", meta = (BindWidget))
	UTextBlock* HeaderText;

	UPROPERTY(EditAnywhere, Category = "Buildings Panel", meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(EditAnywhere, Category = "Buildings Panel", meta = (BindWidget))
	UTextBlock* NextCostText;

	UPROPERTY(EditAnywhere, Category = "Buildings Panel", meta = (BindWidget))
	UButton* UpgradeButton;
	
	virtual void PopulateData(TScriptInterface<IBuilding> building) override;
};

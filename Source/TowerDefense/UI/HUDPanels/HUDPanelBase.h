#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "TowerDefense/Enums/HUDPanelType.h"
#include "TowerDefense/Interfaces/IHUD.h"

#include "HUDPanelBase.generated.h"

UCLASS(ABSTRACT)
class TOWERDEFENSE_API UHUDPanelBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<IHUDInterface> hud;
	
public:
	void Setup(TScriptInterface<IHUDInterface> _hud);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInit();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	HUDPanelType PanelType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShowOnStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PanelPriority = 0;
};

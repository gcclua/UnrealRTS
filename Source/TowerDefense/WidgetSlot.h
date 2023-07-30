#pragma once
#include "Components/CanvasPanelSlot.h"
#include "WidgetSlot.generated.h"

USTRUCT()
struct FWidgetSlot
{
	GENERATED_BODY()
	
public:
	UUserWidget* widget;
	UCanvasPanelSlot* slot;

	FWidgetSlot();
	FWidgetSlot(UUserWidget* _widget, UCanvasPanelSlot* _slot);
};

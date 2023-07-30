#include "WidgetSlot.h"

FWidgetSlot::FWidgetSlot()
{
	widget = nullptr;
	slot = nullptr;
}

FWidgetSlot::FWidgetSlot(UUserWidget* _widget, UCanvasPanelSlot* _slot)
{
	widget = _widget;
	slot = _slot;
}

// MouseController.h: Schnittstelle f�r die Klasse MouseController.
//
//////////////////////////////////////////////////////////////////////
#pragma once
#include "../All2DEngine/Gui/MouseMover.h"
#include "../All2DEngine/Utils/Rect.h"	// Hinzugef�gt von der Klassenansicht
#include "ControllerAdapter.h"


class MouseController : public ControllerAdapter
{
public:
	virtual void pause(bool start=false);
	virtual void generateEvent();
	Rect getPosition();
	bool handleEvent(Event* evt);
	MouseController();
	virtual ~MouseController();
private:
	MouseMover	myMouseMover;
};

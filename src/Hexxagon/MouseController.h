// MouseController.h: Schnittstelle f�r die Klasse MouseController.
//
//////////////////////////////////////////////////////////////////////
#include "..\ALL2DENGINE\UTILS\Rect.h"	// Hinzugef�gt von der Klassenansicht
#pragma once

#include "ControllerAdapter.h"
#include "../All2Dengine/GUI/MouseMover.h"


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

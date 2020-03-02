// MouseController.cpp: Implementierung der Klasse MouseController.
//
//////////////////////////////////////////////////////////////////////

#include "MouseController.h"
#include "hexxagon_messages.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

MouseController::MouseController()
{
	myMouseMover.init();
}

MouseController::~MouseController()
{

}

bool MouseController::handleEvent(Event *evt)
{
	if (evt->Type==HEX_MOUSE_CHANGE)
	{
		evt->Type=MM_MOUSEMOVE;
		evt->lData=(myMouseMover.getPosition().y1<<16) + myMouseMover.getPosition().x1;
		evt->wData=0;
	}
	return myMouseMover.handleEvent(evt);
}

Rect MouseController::getPosition()
{
	return myMouseMover.getPosition();
}

void MouseController::generateEvent()
{}

void MouseController::pause(bool start)
{}

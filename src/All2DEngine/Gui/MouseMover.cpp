// MouseMover.cpp: Implementierung der Klasse MouseMover.
//
//////////////////////////////////////////////////////////////////////

#include "../All2D/All2D_System.h"
#include "MouseMover.h"
#include "../All2D/All2D_Events/MessageManager.h"

#include <string>
using std::string;
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

MouseMover::MouseMover()
{
	isActive=true;
}

MouseMover::~MouseMover()
{
}

bool MouseMover::paint(Image& BackBuffer)
{
	show(BackBuffer);
	return true;
}

bool MouseMover::handleEvent(Event *evt)
{
	if (evt->Type==MM_MOUSEACTIVE)
		isActive=(bool)evt->wData;

	if (isActive)
	{
		switch (evt->Type)
		{
			case MM_MOUSEMOVE:
				blnMouseMoved=true;
				mouseX=evt->lData & 0x0000ffff;
				mouseY=(evt->lData & 0xffff0000)>>16;
				break;

			case MM_LBUTTONDOWN:
				isClicked=true;
				lastClick.x=mouseX;
				lastClick.y=mouseY;
				break;

			case MM_LBUTTONUP:
				isClicked=false;
				break;
		}
	}
	setPosition(mouseX,mouseY);
	return true;
}

void MouseMover::init()	// MousePointerImage wird noch nicht geladen..
{
	mouseX=All2D_System::fixedX*0.5;
	mouseY=All2D_System::fixedY*0.5;
	isClicked=false;

	lastClick.x=-1;
	lastClick.y=-1;
	isInitialized=true;
}


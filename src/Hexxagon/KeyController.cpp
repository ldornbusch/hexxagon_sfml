// KeyController.cpp: Implementierung der Klasse KeyController.
//
//////////////////////////////////////////////////////////////////////

#include <All2D/All2DEngine/All2D/All2D_System.h>
#include <All2D/All2DEngine/All2D/All2D_Events/MessageManager.h>
#include "hexxagon_messages.h"
#include "KeyController.h"


#define ACC_TIME_MS 10
#define MAX_SPEED 15

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

KeyController::KeyController()
{
	iMouseX=All2D_System::fixedX / 2;
	iMouseY=All2D_System::fixedY / 2;
// Default Key Config...
	iUp=sf::Keyboard::Up;
	iDown=sf::Keyboard::Down;
	iLeft=sf::Keyboard::Left;
	iRight=sf::Keyboard::Right;
	iFire=sf::Keyboard::Space;

	for (int x=0;x<4;x++)
		myKeys[x].isDown=false;
}

KeyController::~KeyController()
{

}

bool KeyController::handleEvent(Event *evt)
{
	bool retVal=true;

	if (evt->Type==MM_MOUSEMOVE || evt->Type==MM_LBUTTONDOWN)	// Keine MouseEvents durchlassen!
	{
		retVal=false;
		evt->Type=MM_NO_EVENT;
	}
	if (evt->Type==HEX_MOUSE_CHANGE)
	{
		evt->Type=MM_MOUSEMOVE;
		evt->lData=(iMouseY<<16) + iMouseX;
		evt->wData=0;
	}

	if (evt->Type==MM_KEYDOWN)
	{
		if (evt->wData==iUp)
			pushKey(0);
		if (evt->wData==iDown)
			pushKey(1);
		if (evt->wData==iLeft)
			pushKey(2);
		if (evt->wData==iRight)
			pushKey(3);
		if (evt->wData==iFire)
		{
			evt->Type=MM_LBUTTONDOWN;
			evt->lData=(iMouseY<<16) + iMouseX;
			evt->wData=0;
		}
		evt=processKeyMove(evt);
	}

	if (evt->Type==MM_KEYUP)
	{
		if (evt->wData==iUp)
		{
			evt->Type=MM_MOUSEMOVE;
			releaseKey(0);
		}
		if (evt->wData==iDown)
		{
			evt->Type=MM_MOUSEMOVE;
			releaseKey(1);
		}
		if (evt->wData==iLeft)
		{
			evt->Type=MM_MOUSEMOVE;
			releaseKey(2);
		}
		if (evt->wData==iRight)
		{
			evt->Type=MM_MOUSEMOVE;
			releaseKey(3);
		}
		if (evt->wData==iFire)
		{
			evt->Type=MM_LBUTTONUP;
		}
		if (evt->Type==MM_MOUSEMOVE || evt->Type==MM_LBUTTONUP)
		{
			evt->lData=(iMouseY<<16) + iMouseX;
			evt->wData=0;
		}
	}


	return retVal;
}

Rect KeyController::getPosition()
{
	return Rect(iMouseX,iMouseY);
}

void KeyController::pushKey(int iKeyID)
{
	if (!myKeys[iKeyID].isDown)
	{
		myKeys[iKeyID].isDown=true;
		myKeys[iKeyID].iActualAcc=1;
		myKeys[iKeyID].iStartTime=All2D_System::getTime();
	}
}

void KeyController::releaseKey(int iKeyID)
{
		myKeys[iKeyID].isDown=false;
		myKeys[iKeyID].iActualAcc=0;
		myKeys[iKeyID].iStartTime=0;
}

void KeyController::generateEvent()
{
	Event* tmp=new Event(MM_KEYDOWN,0,0);
	processKeyMove(tmp);
	if (tmp->Type==MM_MOUSEMOVE)
		MessageManager::handleEvent(tmp);
	else
		delete tmp;
}


// we will modify this Message, if a KeyDown occurs to a MouseMove Message
Event* KeyController::processKeyMove(Event *evt)
{
	if (evt->Type!=MM_KEYDOWN)
		return evt;

	if (myKeys[0].isDown)
	{
		myKeys[0].iActualAcc=(All2D_System::getTime()-myKeys[0].iStartTime)/ACC_TIME_MS;
		myKeys[0].iActualAcc=(myKeys[0].iActualAcc>MAX_SPEED)?MAX_SPEED:myKeys[0].iActualAcc;
		iMouseY-=myKeys[0].iActualAcc;
	}
	if (myKeys[1].isDown)
	{
		myKeys[1].iActualAcc=(All2D_System::getTime()-myKeys[1].iStartTime)/ACC_TIME_MS;
		myKeys[1].iActualAcc=(myKeys[1].iActualAcc>MAX_SPEED)?MAX_SPEED:myKeys[1].iActualAcc;
		iMouseY+=myKeys[1].iActualAcc;
	}
	if (myKeys[2].isDown)
	{
		myKeys[2].iActualAcc=(All2D_System::getTime()-myKeys[2].iStartTime)/ACC_TIME_MS;
		myKeys[2].iActualAcc=(myKeys[2].iActualAcc>MAX_SPEED)?MAX_SPEED:myKeys[2].iActualAcc;
		iMouseX-=myKeys[2].iActualAcc;
	}
	if (myKeys[3].isDown)
	{
		myKeys[3].iActualAcc=(All2D_System::getTime()-myKeys[3].iStartTime)/ACC_TIME_MS;
		myKeys[3].iActualAcc=(myKeys[3].iActualAcc>MAX_SPEED)?MAX_SPEED:myKeys[3].iActualAcc;
		iMouseX+=myKeys[3].iActualAcc;
	}
	if (iMouseX<0)
		iMouseX=0;
	if (iMouseX>All2D_System::fixedX)
		iMouseX=All2D_System::fixedX;
	if (iMouseY<0)
		iMouseY=0;
	if (iMouseY>All2D_System::fixedY)
		iMouseY=All2D_System::fixedY;

// New EventMessage: MM_KEYDOWN --> MM_MOUSEMOVE
	if (myKeys[0].isDown ||
		myKeys[1].isDown ||
		myKeys[2].isDown ||
		myKeys[3].isDown)
	{
		evt->Type=MM_MOUSEMOVE;
		evt->lData=(iMouseY<<16) + iMouseX;
		evt->wData=0;
	}
	return evt;
}


void KeyController::pause(bool start)
{}

void KeyController::setKeys(int Up, int Down, int Left, int Right, int Fire)
{
	iUp=Up;
	iDown=Down;
	iLeft=Left;
	iRight=Right;
	iFire=Fire;
}

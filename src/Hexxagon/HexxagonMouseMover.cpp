// HexxagonMouseMover.cpp: Implementierung der Klasse HexxagonMouseMover.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonMouseMover.h"
#include "Hexxagon_messages.h"
#include "../All2DEngine/All2D/All2d_Events/MessageManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HexxagonMouseMover::HexxagonMouseMover()
{
	Player1=NULL;
	Player2=NULL;
	defaultController=NULL;
	actPlayer=0;
	blnPause=true;
}

HexxagonMouseMover::~HexxagonMouseMover()
{
}

void HexxagonMouseMover::getGFX(Image &imgGFX)
{
	MouseMover::init();
	GameImageCloner::getGFX(imgGFX);
	cloneImage(imgElements);
	setSrcRect(Rect(0,160,64,64));
	setPosition(RECT_INVALID,RECT_INVALID,64,64);
	setOffset(48,0);
	MouseMover::setBlitMode(IMAGE_BLTMODE_TRANS);
	MouseMover::setPriority(50);
}

void HexxagonMouseMover::setController(ControllerAdapter* ctrl1,ControllerAdapter* ctrl2)
{
	Player1=ctrl1;
	Player2=ctrl2;
}
void HexxagonMouseMover::setDefault(ControllerAdapter* defCtrl)
{
	defaultController=defCtrl;
}

bool HexxagonMouseMover::handleEvent(Event *evt)
{
	bool retVal=false;
	switch (evt->Type)
	{
	case MM_LBUTTONUP:	//if mouse invisible supress mouseEvents
	case MM_LBUTTONDOWN:	//if mouse invisible supress mouseEvents
	case MM_MOUSEMOVE:	//if mouse invisible supress mouseEvents
		if (actPlayer==2 && !blnPause)
			evt->Type=MM_NO_EVENT;
		break;
	case A3D_XMLMENU_APPEAR:
		blnPause=true;
		Player1->pause(true);
		Player2->pause(true);
		setSrcRect(Rect(0,160,64,64));	// neutral Pointer
		break;
	case A3D_XMLMENU_DISAPPEAR:
		blnPause=false;
		Player1->pause(false);
		Player2->pause(false);
		if (actPlayer==-1)
			setSrcRect(Rect(64,160,64,64));
		if (actPlayer==1)
			setSrcRect(Rect(128,160,64,64));
		if (actPlayer==2)
		{
			blnPause=true;
			setSrcRect(Rect(0,0,1,1));
		}
		if (actPlayer==0)
		{
			blnPause=true;
			setSrcRect(Rect(0,160,64,64));
		}
		break;
	case HEX_MOUSE_CHANGE:
		switch (evt->wData)
		{
		case -1:		// Dark Hand (Blue)
			blnPause=false;
			setSrcRect(Rect(64,160,64,64));
			break;
		case +1:		// Bright Hand (Red)
			blnPause=false;
			setSrcRect(Rect(128,160,64,64));
			break;
		case 2:			// keine Hand
//			blnPause=true;
			setSrcRect(Rect(0,0,1,1));
			break;
		case 0:			// neutrale Hand
		default:		// nix machen
			blnPause=true;
			setSrcRect(Rect(0,160,64,64));
			break;
		}
		actPlayer=evt->wData;
		
	default:
		break;
	}
	if (!blnPause)
	{
		switch (actPlayer)
		{
			case 1:
				if (Player1)
				{
					retVal=Player1->handleEvent(evt);
					setPosition(Player1->getPosition());
				}
			break;
			case -1:
				if (Player2)
				{
					retVal=Player2->handleEvent(evt);
					setPosition(Player2->getPosition());
				}
			break;
			case 2:	// means: no action!
				retVal=true;
				break;
			default:
				retVal=MouseMover::handleEvent(evt);
				retVal=false;
			break;
		}
	} else {
		if (defaultController)
		{
			defaultController->handleEvent(evt);
			setPosition(defaultController->getPosition());
			retVal=true;
		}
	}
	return retVal;
}

bool HexxagonMouseMover::paint(Image &imgBackBuffer)
{
	if (!blnPause)
	{
		Player1->generateEvent();
		Player2->generateEvent();
	}
	return MouseMover::paint(imgBackBuffer);
}

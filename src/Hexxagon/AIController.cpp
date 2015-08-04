// AIController.cpp: Implementierung der Klasse AIController.
//
//////////////////////////////////////////////////////////////////////

#include "AIController.h"
#include "../All2DEngine/all2D/All2D_System.h"
#include "../All2DEngine/all2D/All2D_Events/MessageManager.h"

#include "Hexxagon_messages.h"
#define AI_THINKTIME 500
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

AIController::AIController()
{
	UIMovableSprite::setTime(AI_THINKTIME);
	blnSetFrom=blnSetTo=true;
	blnPause=false;
	iSleepTime=0;
}

AIController::~AIController()
{

}

bool AIController::handleEvent(Event *evt)
{
	bool retVal=true;
	if (blnPause)
		return true;

	if (evt->Type==MM_MOUSEMOVE || evt->Type==MM_LBUTTONDOWN)	// Keine MouseEvents durchlassen(nur wenn pausiert)!
	{
		retVal=false;
		evt->Type=MM_NO_EVENT;
	}
/*	if (evt->Type==MM_KEYDOWN && evt->wData==VK_ESCAPE)	// Keine Escape Taste durchlassen!
	{
		retVal=false;
		evt->Type=MM_NO_EVENT;
	}
*/	if (evt->Type==HEX_AI_MOUSE_MOVE)	// MouseEvents umwandeln und durchlassen!
		evt->Type=MM_MOUSEMOVE;
	if (evt->Type==HEX_AI_MOUSE_CLICK)	// MouseEvents umwandeln und durchlassen!
		evt->Type=MM_LBUTTONDOWN;

	if (evt->Type==HEX_MOUSE_CHANGE)
	{
		iStartTime=All2D_System::getTime();
		newMove = AIBrain.getBestMove(iPlayerID,vecStones);
		UIMovableSprite::setTarget(vecStones[newMove.from]->getPosition().x1,vecStones[newMove.from]->getPosition().y1);
		blnSetFrom=blnSetTo=false;
	}

	return retVal;
}

Rect AIController::getPosition()
{
	return UIMovableSprite::getPosition();
}

void AIController::generateEvent()
{
	int iNow=All2D_System::getTime();
	int x,y;
	UIMovableSprite::updatePosition();

	bool alreadysent=false;

	if (iNow-iStartTime>AI_THINKTIME && !blnSetFrom)
	{
		setTarget(vecStones[newMove.to]->getPosition().x1,vecStones[newMove.to]->getPosition().y1);
		vecStones[newMove.from]->fire();
		blnSetFrom=true;
		alreadysent=true;
	}
	if (iNow-iStartTime>2*AI_THINKTIME && !blnSetTo)
	{
		vecStones[newMove.to]->fire();
		blnSetTo=true;
		alreadysent=true;
	}
	if (!alreadysent)	// Falls kein Klick generiert wurde..generiere einen Move..
	{
		Event* evt=new Event(HEX_AI_MOUSE_MOVE,0,0);
		x=getPosition().x1;
		y=getPosition().y1;
		evt->lData=(y<<16) + x;
		MessageManager::handleEvent(evt);
	}
}

void AIController::setStones(const vector<HexxagonStone*>& vec)
{
	vecStones=vec;
}

void AIController::setPlayerID(int iID)
{
	iPlayerID=iID;
}

void AIController::pause(bool start)
{
	if (start)	//start == true-->go to sleep mode
	{
		iSleepTime=All2D_System::getTime();
		UIMovableSprite::pause(start);
	}
	if (!start)	// start == false --> wake up
	{
		if (iSleepTime!=0)	// sleeptime set?
		{
			int iSleepDuration=All2D_System::getTime()-iSleepTime;
			iStartTime+=iSleepDuration;
		}
		UIMovableSprite::pause(start);
	}
	blnPause=start;
}

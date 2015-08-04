// UIMovableSprite.cpp: Implementierung der Klasse UIMovableSprite.
//
//////////////////////////////////////////////////////////////////////

#include "UIMovableSprite.h"
#include "../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UIMovableSprite::UIMovableSprite()
{
	moveType=MOVETYPE_FIX_TIME;
	ptSpeed.x=1;
	ptSpeed.y=1;
	time2ReachTarget=1000;	// 1 sec to reach target...
	startTime=0;
	blnPause=false;
	iSleepTime=0;
}

UIMovableSprite::~UIMovableSprite()
{

}
void UIMovableSprite::pause(bool start)
{
	
	if (start)	//start == true-->go to sleep mode
	{
		iSleepTime=All2D_System::getTime();
	}
	if (!start)	// start == false --> wake up
	{
		if (iSleepTime!=0)	// sleeptime set?
		{
			int iSleepDuration=All2D_System::getTime()-iSleepTime;
			startTime+=iSleepDuration;
		}
	}
	blnPause=start;
}

void UIMovableSprite::setTarget(int x, int y)
{
	ptTarget.x=x;
	ptTarget.y=y;

	ptStart=Point(Position.x1, Position.y1);
	startTime=All2D_System::getTime();
}

bool UIMovableSprite::destinationReached()
{
	return (ptTarget.x==Position.x1 && ptTarget.y==Position.y1);
}

void UIMovableSprite::setSpeed(int xSpeed, int ySpeed)
{
	ptSpeed.x=xSpeed;
	ptSpeed.y=ySpeed;

}

Point UIMovableSprite::getSpeed()
{
	return ptSpeed;
}

void UIMovableSprite::setTime(int milliSec)
{
	time2ReachTarget=milliSec;
}

void UIMovableSprite::setMoveType(int movType)
{
	moveType = movType;
}

Point UIMovableSprite::getTarget()
{
	return ptTarget;
}

void UIMovableSprite::onTargetReached()
{
}

// gibt true beim ersten Erreichen des Ziels zurück...
void UIMovableSprite::setNewPosition()
{
	switch (moveType)
	{
	case MOVETYPE_FIX_SPEED:
		updatePositionFixSpeed();
		break;
	case MOVETYPE_FIX_TIME:
		updatePositionFixTime();
		break;
	}
}

void UIMovableSprite::triggerEvent()
{
	// sind wir jetzt am Ziel?
	if (destinationReached())
		onTargetReached();
}

bool UIMovableSprite::updatePosition()
{
	if (destinationReached())		// Wenn Ziel schon erreicht worden ist, dan nnicht mehr die Funktion updaten
		return false;
	
	setNewPosition();
	
	triggerEvent();
	
	return destinationReached();
}

void UIMovableSprite::updatePositionFixTime()
{
	if (startTime<0)	//Target reached -> startTime=-1
		return;
	
	int actTime=All2D_System::getTime() - startTime;
	double factor;
	if (actTime==0)
		factor=0.0;
	else
		factor=(float)actTime/(float)time2ReachTarget;

	
	if (factor>1.0f)	//Target Reached?
	{
		Position.x1=ptTarget.x;
		Position.y1=ptTarget.y;
		startTime=-1;						// Target Reached, no PositionUpdates needed
		return;
	}
	
	int dx=ptTarget.x-ptStart.x;
	int dy=ptTarget.y-ptStart.y;

	Position.x1=ptStart.x+factor*dx;
	Position.y1=ptStart.y+factor*dy;

}

void UIMovableSprite::updatePositionFixSpeed()
{

	int dx=ptTarget.x-Position.x1;
	int dy=ptTarget.y-Position.y1;

	if (dx>0){
		if (dx<ptSpeed.x && dx>0) 
			Position.x1=ptTarget.x;
		else
			Position.x1+=ptSpeed.x;
	} else {
		if (dx>-ptSpeed.x && dx<=0) 
			Position.x1=ptTarget.x;
		else
			Position.x1-=ptSpeed.x;
	}
	if (dy>0) 
	{
		if (dy<ptSpeed.y && dy>0) 
			Position.y1=ptTarget.y;
		else
			Position.y1+=ptSpeed.y;
	} else {
		if (dy>-ptSpeed.y && dy<=0) 
			Position.y1=ptTarget.y;
		else
			Position.y1-=ptSpeed.y;
	}



}

void UIMovableSprite::stop()
{
	ptTarget=Point(Position.x1, Position.y1);
}

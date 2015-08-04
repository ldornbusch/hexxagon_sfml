// UIMovableSprite.h: Schnittstelle f�r die Klasse UIMovableSprite.
//
// Ein Movable Sprite kann in einer bestimmten Zeit, oder in einer 
// bestimmten Geschwindigkeit ein bestimmtes Ziel erreichen. Die aktuelle 
// Position wird durch updatePosition() berechnet. Diese Funktion gibt 
// genau dann true zurueck, wenn der Zielpunkt erreicht wurde. Falls updatePosition
// dann nochmals aufgerufen wird, gibt sie aber wieder false zur�ck..
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIMOVABLESPRITE_H__F7823491_1A9D_4D92_B9E1_420546FB5F75__INCLUDED_)
#define AFX_UIMOVABLESPRITE_H__F7823491_1A9D_4D92_B9E1_420546FB5F75__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UISprite.h"
#include "../../UTILS/POINT.H"	// Hinzugef�gt von der Klassenansicht
#include "../../UTILS/Vector.h"	// Hinzugef�gt von der Klassenansicht

#define MOVETYPE_FIX_SPEED 0x0001	// der Sprite bewegt sich _immer_ mit der selben Geschwindigkeit
#define MOVETYPE_FIX_TIME  0x0002	// Der Sprite bewegt sich _immer_ in der selben Zeit zu einem gegebenen Punkt


class UIMovableSprite : virtual public UISprite  
{
public:
	virtual void stop();
	virtual void pause(bool blnPause);
	virtual void onTargetReached();
	virtual bool updatePosition();
	virtual void setTarget(int x, int y);
	Point getTarget();
	Point getSpeed();
	void setMoveType(int movType);
	void setTime(int milliSec);
	void setSpeed(int xSpeed, int ySpeed);
	bool destinationReached();
	UIMovableSprite();
	virtual ~UIMovableSprite();
protected:
	void setNewPosition();
	void triggerEvent();
	void updatePositionFixSpeed();
	void updatePositionFixTime();
private:
	bool blnPause;
	int iSleepTime;
	bool blnHasReached;
	int startTime;			// Time when Movement started..
	int time2ReachTarget;	// Time to reach Target ( only in FixTime Mode valid)
	int moveType;			// Type of Movement(either FixTime, or FixSpeed)
	Point ptSpeed;			// Speed of Movement(only in FixSpeed valid)
	Point ptTarget;			// the TargetPoint to reach..
	Point ptStart;			// We need the Start for FixTimeMovement Interpolation
};

#endif // !defined(AFX_UIMOVABLESPRITE_H__F7823491_1A9D_4D92_B9E1_420546FB5F75__INCLUDED_)

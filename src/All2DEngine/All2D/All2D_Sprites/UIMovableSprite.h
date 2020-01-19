// UIMovableSprite.h: Schnittstelle für die Klasse UIMovableSprite.
//
// Ein Movable Sprite kann in einer bestimmten Zeit, oder in einer
// bestimmten Geschwindigkeit ein bestimmtes Ziel erreichen. Die aktuelle
// Position wird durch updatePosition() berechnet. Diese Funktion gibt
// genau dann true zurueck, wenn der Zielpunkt erreicht wurde. Falls updatePosition
// dann nochmals aufgerufen wird, gibt sie aber wieder false zurück..
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UISprite.h"
#include "../../UTILS/POINT.H"	// Hinzugefügt von der Klassenansicht
#include "../../UTILS/Vector.h"	// Hinzugefügt von der Klassenansicht

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
	bool blnHasReached;
	unsigned int iSleepTime;
	unsigned int startTime;			// Time when Movement started..
	unsigned int time2ReachTarget;	// Time to reach Target ( only in FixTime Mode valid)
	int moveType;			// Type of Movement(either FixTime, or FixSpeed)
	Point ptSpeed;			// Speed of Movement(only in FixSpeed valid)
	Point ptTarget;			// the TargetPoint to reach..
	Point ptStart;			// We need the Start for FixTimeMovement Interpolation
};

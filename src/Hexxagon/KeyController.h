// KeyController.h: Schnittstelle für die Klasse KeyController.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "ControllerAdapter.h"

struct keyStroke
{
	bool	isDown;
	int		iStartTime;
	int		iActualAcc;
};
class KeyController : public ControllerAdapter
{
public:
	void setKeys(int Up, int Down, int Left, int Right, int Fire);
	virtual void pause(bool start=false);
	virtual void generateEvent();
	Rect getPosition();
	bool handleEvent(Event* evt);
	KeyController();
	virtual ~KeyController();

private:
	Event* processKeyMove(Event* evt);
	void pushKey(int iKeyID);
	void releaseKey(int iKeyID);
	keyStroke myKeys[4];
	unsigned int iUp, iDown, iLeft, iRight, iFire;	// The KeyIDs, which are received in HandleEventFunction
	int iMouseX, iMouseY;
};

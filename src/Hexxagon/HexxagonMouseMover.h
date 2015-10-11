// HexxagonMouseMover.h: Schnittstelle für die Klasse HexxagonMouseMover.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\ALL2DENGINE\GUI\MouseMover.h"
#include "..\game\GameImageCloner.h"
#include "ControllerAdapter.h"

class HexxagonMouseMover : public MouseMover , GameImageCloner
{
public:
	virtual bool paint(Image& imgBackBuffer);
	virtual bool handleEvent(Event* evt);
	HexxagonMouseMover();
	virtual ~HexxagonMouseMover();
	void getGFX(Image &imgGFX);
	void setController(ControllerAdapter* ctrl1,ControllerAdapter* ctrl2);
	void setDefault(ControllerAdapter* defCtrl);
	ControllerAdapter*	Player1, *Player2, *defaultController;		// ControllerAdapter for Player 1 and 2
private:
	int actPlayer;
	bool blnPause;
};

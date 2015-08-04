// HexxagonMouseMover.h: Schnittstelle für die Klasse HexxagonMouseMover.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONMOUSEMOVER_H__28C47C50_6313_4946_8B09_069B74E5E5AD__INCLUDED_)
#define AFX_HEXXAGONMOUSEMOVER_H__28C47C50_6313_4946_8B09_069B74E5E5AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_HEXXAGONMOUSEMOVER_H__28C47C50_6313_4946_8B09_069B74E5E5AD__INCLUDED_)

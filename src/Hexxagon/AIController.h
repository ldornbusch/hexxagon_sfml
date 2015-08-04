// AIController.h: Schnittstelle für die Klasse AIController.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AICONTROLLER_H__5641C9C3_CDE8_48CB_940C_07DD9F9FEDBA__INCLUDED_)
#define AFX_AICONTROLLER_H__5641C9C3_CDE8_48CB_940C_07DD9F9FEDBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControllerAdapter.h"
#include "../All2DEngine/All2D/All2D_Sprites/UIMovableSprite.h"
#include "HexxagonMove.h"	// Hinzugefügt von der Klassenansicht
#include "HexxagonAIPlayer.h"	// Hinzugefügt von der Klassenansicht

class AIController :	public ControllerAdapter,
						public virtual UIMovableSprite 
					 
{
public:
	virtual void pause(bool start=false);
	void setPlayerID(int iID);
	void setStones(const vector<HexxagonStone*>& vec);
	HexxagonMove newMove;
	virtual void generateEvent();
	Rect getPosition();
	bool handleEvent(Event* evt);
	AIController();
	virtual ~AIController();

private:
	bool blnSetTo;
	bool blnSetFrom;
	bool blnPause;
	int iPlayerID;
	int iStartTime;
	int iSleepTime;
	HexxagonAIPlayer AIBrain;
	vector<HexxagonStone*> vecStones;

};

#endif // !defined(AFX_AICONTROLLER_H__5641C9C3_CDE8_48CB_940C_07DD9F9FEDBA__INCLUDED_)

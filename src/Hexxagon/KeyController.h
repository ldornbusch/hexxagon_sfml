// KeyController.h: Schnittstelle für die Klasse KeyController.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYCONTROLLER_H__8890C19E_2EA6_449D_975D_CBDDFD3EAC18__INCLUDED_)
#define AFX_KEYCONTROLLER_H__8890C19E_2EA6_449D_975D_CBDDFD3EAC18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	int iUp, iDown, iLeft, iRight, iFire;	// The KeyIDs, which are received in HandleEventFunction
	int iMouseX, iMouseY;
};

#endif // !defined(AFX_KEYCONTROLLER_H__8890C19E_2EA6_449D_975D_CBDDFD3EAC18__INCLUDED_)

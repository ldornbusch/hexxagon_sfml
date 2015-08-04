// MouseController.h: Schnittstelle für die Klasse MouseController.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSECONTROLLER_H__8052B1CE_9EB3_4B4A_BD60_B172027ABDED__INCLUDED_)
#define AFX_MOUSECONTROLLER_H__8052B1CE_9EB3_4B4A_BD60_B172027ABDED__INCLUDED_

#include "..\ALL2DENGINE\UTILS\Rect.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControllerAdapter.h"
#include "../All2Dengine/GUI/MouseMover.h"


class MouseController : public ControllerAdapter  
{
public:
	virtual void pause(bool start=false);
	virtual void generateEvent();
	Rect getPosition();
	bool handleEvent(Event* evt);
	MouseController();
	virtual ~MouseController();
private:
	MouseMover	myMouseMover;
};

#endif // !defined(AFX_MOUSECONTROLLER_H__8052B1CE_9EB3_4B4A_BD60_B172027ABDED__INCLUDED_)

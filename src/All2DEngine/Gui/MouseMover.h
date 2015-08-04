// MouseMover.h: Schnittstelle für die Klasse MouseMover.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOUSEMOVER_H__6663FC82_FA0B_11D4_B046_00E098802DF2__INCLUDED_)
#define AFX_MOUSEMOVER_H__6663FC82_FA0B_11D4_B046_00E098802DF2__INCLUDED_

#include "../All2D/All2D_Sprites/Anim.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MouseMover : public UISprite
{
public:
	void init();
	virtual bool handleEvent(Event* evt);
	virtual bool paint(Image& BackBuffer);
	MouseMover();
	virtual ~MouseMover();

protected:
	bool blnMouseMoved;
	bool isActive;
	Point lastClick;
	bool isClicked;
	int mouseX,	mouseY;
};

#endif // !defined(AFX_MOUSEMOVER_H__6663FC82_FA0B_11D4_B046_00E098802DF2__INCLUDED_)

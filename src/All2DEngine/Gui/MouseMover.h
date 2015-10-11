// MouseMover.h: Schnittstelle für die Klasse MouseMover.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2D/All2D_Sprites/Anim.h"	// Added by ClassView

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

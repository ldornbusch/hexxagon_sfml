// UIElement.h: Schnittstelle für die Klasse UIElement.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2D_Base/xElement.h"
#include "../../Utils/Rect.h"

class UIElement :public xElement
{
public:
	void setEnabled(bool e);
	bool isEnabled();
	bool mouseInside();
	bool getFocus();
	virtual bool handleEvent(Event* evt);
	Rect getPosition();
	virtual bool isInside(int x, int y);
	virtual void setPosition(Rect p);
	virtual void setPosition(int x=RECT_INVALID,int y=RECT_INVALID, int w=RECT_INVALID, int h=RECT_INVALID);
	UIElement();
	virtual ~UIElement();

protected:
	bool blnAbsolutePlacing;
	bool enabled;
	bool mouseIn;
	bool focus;
	Rect Position;

};

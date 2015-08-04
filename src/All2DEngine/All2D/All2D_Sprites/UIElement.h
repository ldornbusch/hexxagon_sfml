// UIElement.h: Schnittstelle für die Klasse UIElement.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIELEMENT_H__722FB595_98FE_46DD_9B54_15CEF4A3E99D__INCLUDED_)
#define AFX_UIELEMENT_H__722FB595_98FE_46DD_9B54_15CEF4A3E99D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2D_Base/xElement.h"
#include "../../utils/RECT.h"

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

#endif // !defined(AFX_UIELEMENT_H__722FB595_98FE_46DD_9B54_15CEF4A3E99D__INCLUDED_)

// UIDragableSprite.h: Schnittstelle für die Klasse UIDragableSprite.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2D/All2D_Sprites/UISprite.h"
#include "..\UTILS\POINT.H"	// Added by ClassView
#include "..\UTILS\Rect.h"	// Added by ClassView

class UIDragableSprite : virtual public UISprite
{
public:
	bool isDragged();
	void setClipRect(Rect clip);
	virtual void click();
	virtual void drop();
	virtual bool handleEvent(Event *evt);

	UIDragableSprite();
	UIDragableSprite(Image &clone);
	virtual ~UIDragableSprite();

protected:
	bool hasMoved;
	bool drag;
private:
	Point clipPosition(Point p);
	Rect rctClipRect;
};

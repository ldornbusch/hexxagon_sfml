// UIDragableSprite.h: Schnittstelle für die Klasse UIDragableSprite.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2D/All2D_Sprites/UISprite.h"
#include "../Utils/Point.h"
#include "../Utils/Rect.h"

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

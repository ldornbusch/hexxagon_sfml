// UIDragableSprite.h: Schnittstelle für die Klasse UIDragableSprite.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIDRAGABLESPRITE_H__5D5A67CE_1C8B_45C4_91EC_C7E85D33E273__INCLUDED_)
#define AFX_UIDRAGABLESPRITE_H__5D5A67CE_1C8B_45C4_91EC_C7E85D33E273__INCLUDED_

#include "..\UTILS\POINT.H"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2D/All2D_Sprites/UISprite.h"
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

#endif // !defined(AFX_UIDRAGABLESPRITE_H__5D5A67CE_1C8B_45C4_91EC_C7E85D33E273__INCLUDED_)

// UIDragableSprite.cpp: Implementierung der Klasse UIDragableSprite.
//
//////////////////////////////////////////////////////////////////////

#include "UIDragableSprite.h"
#include "../All2D/All2D_System.h"
#include "../All2D/All2D_Events/MessageManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UIDragableSprite::UIDragableSprite()
{
	drag=false;
}

UIDragableSprite::UIDragableSprite(Image &clone) : UISprite(clone)
{
	drag=false;
}

UIDragableSprite::~UIDragableSprite()
{

}

bool UIDragableSprite::handleEvent(Event *evt)
{
	bool retVal=true;
	static Point p, dragOffset, oldOffset;
	switch (evt->Type)
	{
		case MM_LBUTTONDOWN:
			p=All2D_System::extractMouseCoords(evt);
			drag=isInside(p.x,p.y) ;
			if (drag)
			{
				oldOffset=getOffset();
				dragOffset=Point(p.x-getPosition().x1+getOffset().x,p.y-getPosition().y1+getOffset().y);
			}
			hasMoved=false;
		break;
		case MM_MOUSEMOVE:
			p=All2D_System::extractMouseCoords(evt);
			hasMoved=drag;
			if (hasMoved)
				setOffset(dragOffset.x,dragOffset.y);
			break;
		case MM_LBUTTONUP:
			if (drag){
				if(hasMoved)
				{
					drop();
					p.x+=oldOffset.x-getOffset().x;
					p.y+=oldOffset.y-getOffset().y;
					setOffset(oldOffset.x,oldOffset.y);
					setPosition(p.x,p.y);
					retVal=false;// signal an aufrufer: sprite wurde gedropped
				}
				else{
					click();
                }
            }
			drag=false;
			break;
	}

	if (drag && hasMoved)
	{
		if (!(rctClipRect==Rect()))
			p=clipPosition(p);
		setPosition(p.x,p.y);
		retVal=false;
	}
	return retVal;

}

void UIDragableSprite::setClipRect(Rect clip)
{
	rctClipRect.setPosition(clip.x1,clip.y1,clip.x2,clip.y2);
}

void UIDragableSprite::drop()
{}

void UIDragableSprite::click()
{}

Point UIDragableSprite::clipPosition(Point p)
{
	if (!rctClipRect.isInside(p.x,p.y));
	{
		if (p.x-getOffset().x<rctClipRect.x1)
			p.x=rctClipRect.x1+getOffset().x;
		if (p.y-getOffset().y<rctClipRect.y1)
			p.y=rctClipRect.y1+getOffset().y;
		if (p.x-getOffset().x>rctClipRect.x1+rctClipRect.x2)
			p.x=rctClipRect.x1+rctClipRect.x2+getOffset().x;
		if (p.y-getOffset().y>rctClipRect.y1+rctClipRect.y2)
			p.y=rctClipRect.y1+rctClipRect.y2+getOffset().y;

	}
	return p;
}

bool UIDragableSprite::isDragged()
{
	return drag;
}

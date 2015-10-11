// UIHoverButton.cpp: Implementierung der Klasse UIHoverButton.
// Erzeugt einen Button der beim Überfahren mit der Maus ein Hovereffekt
// Darstellt.. dies kann ein anderer BlitMode, oder ein anderes Bild sein
//////////////////////////////////////////////////////////////////////

#include "UIHoverButton.h"
#include "../All2D/All2D_System.h"
#include "../All2D/All2D_Events/MessageManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UIHoverButton::UIHoverButton() : HoverImage()
{
	isHover=false;
	iHoverBltMode=IMAGE_BLTMODE_TRANS;
	setHoverFlag(MM_NAVIGATION_HOVER,getID());
}

UIHoverButton::~UIHoverButton()
{

}
bool UIHoverButton::handleEvent(Event *evt)
{
	Point p;
	if (enabled){
		switch (evt->Type)
		{
				case MM_MOUSEMOVE:
					// set mouseIn according to focus, check if it is relative, or absolute positioned
					p=All2D_System::extractMouseCoords(evt);
					if ( isInside(p.x,p.y) )
					{
	//					needUpdate=true;
						isHover=true;
						if (!mouseIn )		// Gerade erst reingekommen...
						{
							if (hoverFlag!=0) {
									MessageManager::handleEvent(new Event(hoverFlag,hoverWord, HOVER_ON));
							}
							enter();
						}
						mouseIn=true;
					} else {
	//					needUpdate=true;
						isHover=false;
						// hover out event ???
						if (mouseIn){
							if (hoverFlag!=0)
								MessageManager::handleEvent(new Event(hoverFlag,hoverWord, HOVER_OFF));
							leave();
						}
						mouseIn=false;
					}
					break;
		}
	}
	return UIButton::handleEvent(evt);

}

bool UIHoverButton::paint(Image& Backbuffer)
{
	if (bVisible){
		if (isHover)
		{
			HoverImage.setPosition(getPosition().x1,getPosition().y1,getPosition().x2,getPosition().y2);
			HoverImage.show(Backbuffer, iHoverBltMode);
		}else{
			UISprite::paint(Backbuffer);
		}
    }
	return true;
}
// Diese Werte werden gesendet, wenn  die Maus in den Hoverbereich eintritt.
void UIHoverButton::setHoverFlag(int i, unsigned int w)
{
	hoverFlag=i;
	hoverWord=w;
}

int UIHoverButton::getHeight()
{
	int retVal=RECT_INVALID;
	if (isHover && UISprite::getHeight()==RECT_INVALID)
		retVal=HoverImage.getHeight();
	else
		retVal=UISprite::getHeight();
	return retVal;
}

int UIHoverButton::getWidth()
{
	int retVal=RECT_INVALID;
	if (isHover && UISprite::getWidth()==RECT_INVALID)
		retVal=HoverImage.getWidth();
	else
		retVal=UISprite::getWidth();
	return retVal;
}


void UIHoverButton::setPriority(int prio)
{
	UISprite::setPriority(prio);
	HoverImage.setPriority(prio);
}
void UIHoverButton::setOffset(int x, int y)
{
	UISprite::setOffset(x,y);
	HoverImage.setOffset(x,y);
}

void UIHoverButton::finish()
{
	HoverImage.finish();
	UISprite::finish();
}

void UIHoverButton::init()
{
	isHover=false;
}

void UIHoverButton::setHoverStatus(bool blnFlag)
{
	isHover=blnFlag;
}

bool UIHoverButton::getHoverStatus()
{
	return isHover;
}

void UIHoverButton::setHoverImage(Image &img)
{
	HoverImage.cloneImage(img);
}

void UIHoverButton::setHoverBlitMode(int ibltMode)
{
	iHoverBltMode=ibltMode;
}
void UIHoverButton::leave(){}
void UIHoverButton::enter(){}

void UIHoverButton::setPosition(Rect rctPos)
{
	UISprite::setPosition(rctPos);
}

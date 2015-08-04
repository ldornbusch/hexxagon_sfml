// UIScrollArea.cpp: implementation of the UIScrollArea class.
//
//////////////////////////////////////////////////////////////////////

#include "../All2D/All2D_System.h"
#include "UIScrollArea.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UIScrollArea::UIScrollArea()
{
	setFont(All2D_System::SystemFont);

}

UIScrollArea::~UIScrollArea()
{

}

bool UIScrollArea::paint(Image& backBuffer)
{
	return UISprite::paint(backBuffer);
}

bool UIScrollArea::handleEvent(Event* evt)
{
	return UISprite::handleEvent(evt);
}

void UIScrollArea::setFont(ImageText& fnt)
{
	fntFont.cloneFont(fnt);
}
// only empty functions.. scrollarea has no changeable Values..
string UIScrollArea::getName()
{	return UISprite::getName();}

value UIScrollArea::getValue()
{	return value("",0);}

void UIScrollArea::setValue(value val)
{}

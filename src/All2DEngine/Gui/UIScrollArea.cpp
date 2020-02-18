// UIScrollArea.cpp: implementation of the UIScrollArea class.
//
//////////////////////////////////////////////////////////////////////

#include "../All2D/All2D_System.h"
#include "UIScrollArea.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UIScrollArea::UIScrollArea():xContainer("scrollarea")
{
}

UIScrollArea::~UIScrollArea()
{
}

bool UIScrollArea::paint(Image& backBuffer)
{
    int y_off = content.getHeight() - getHeight() - vertical_Scroller.getValue().second;
	content.setSrcRect(Rect(0, y_off,
                        getWidth() - vertical_Scroller.getWidth(), getHeight()));
	return xContainer::paint(backBuffer);;
}

bool UIScrollArea::handleEvent(Event* evt)
{
	return xContainer::handleEvent(evt);
}
void UIScrollArea::setImage(Image& pic){
    content.resize(pic.getWidth(), pic.getHeight());
    content.setPriority(getPriority());
    content.setPosition(getPosition());
    pic.show(content,0,0);
    add(content);
    if(content.getHeight() > getHeight()){
        Rect r = getPosition();
        r.x1+=getWidth() - 12;
        r.x2 = 12;
        vertical_Scroller.setPosition(r);
        vertical_Scroller.setPriority(getPriority()+1);
        int max_val = content.getHeight() - getHeight();
        vertical_Scroller.setButtonProperties(max_val,0,4);
        vertical_Scroller.setValue(value("",max_val));
        add(vertical_Scroller);
	}
}

void UIScrollArea::setName(string n)
{	UISprite::setName(n);}

// only empty functions.. scrollarea has no changeable Values..
string UIScrollArea::getName()
{	return UISprite::getName();}

value UIScrollArea::getValue()
{	return value("",0);}

void UIScrollArea::setValue(value val)
{}


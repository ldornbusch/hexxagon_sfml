// UIScrollBar.cpp: implementation of the UIScrollBar class.
//   btnUp    sprtSlider   Background   btnDown
//   __|___________|_______|____________|__
//   |<-|        |xxxxxx|              |->|
//   --------------------------------------
//
// Dies sind die Funktionalen Elemente des Scrollbars
//////////////////////////////////////////////////////////////////////

#include "UIScrollBar.h"

#include "../All2D/All2D_System.h"

#define SCROLLBAR_MAX_SIZE 20
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UIScrollBar::UIScrollBar(int iMode)
{

	Image::cloneImage(All2D_System::UIElements,Rect(16,0,48,16));
	btnUp.cloneImage(*this);
	btnDown.cloneImage(*this);
	sprtSlider.cloneImage(*this);
	btnUp.setSendFlag(MM_SCROLL_UP,getID());
	btnDown.setSendFlag(MM_SCROLL_DOWN,getID());

	setScrollBarMode(iMode);

	Image tmp;
	tmp.cloneImage(All2D_System::UIElements,Rect(16,16,48,16));
	setHoverImage(tmp);

	setBlitMode(IMAGE_BLTMODE_TRANS);
	setHoverBlitMode(IMAGE_BLTMODE_TRANS);

	setButtonProperties();
	setValue(value("",iMinValue));
}

UIScrollBar::~UIScrollBar()
{

}

void UIScrollBar::setButtonProperties(int Max, int Min, int ButtonSpeed, int PageSpeed, int SliderSize)
{
	iMinValue=Min;
	iMaxValue=Max;
	iButtonSpeed=ButtonSpeed;
	iPageSpeed=PageSpeed;
	iSliderSize=SliderSize;
}
void UIScrollBar::setScrollBarMode(int iMode)
{
	iScrollBarMode=iMode;
	if (getScrollBarMode()==ALL2D_VERTICAL)
		setSrcRect(Rect(0,0,8,8),Rect(0,8,8,8),Rect(32,0,8,8),Rect(40,0,8,8));
	else
		setSrcRect(Rect(16,0,8,8),Rect(16,8,8,8),Rect(32,0,8,8),Rect(40,0,8,8));

}

int UIScrollBar::getScrollBarMode()
{	return iScrollBarMode;}

bool UIScrollBar::handleEvent(Event *evt)
{
	if (evt->Type==MM_SCROLL_UP && evt->wData==getID())
		iActualValue+=iButtonSpeed;
	if (evt->Type==MM_SCROLL_DOWN && evt->wData==getID())
		iActualValue-=iButtonSpeed;

	if (evt->Type==MM_LBUTTONDOWN)
	{
		Point pt=All2D_System::extractMouseCoords(evt);
		if( isInside(pt.x,pt.y)&&
			!btnUp.isInside(pt.x,pt.y)&&
			!btnDown.isInside(pt.x,pt.y)&&
			!sprtSlider.isInside(pt.x,pt.y))
		{
			if (getScrollBarMode()==ALL2D_VERTICAL)
			{
				if (sprtSlider.getPosition().y1>pt.y)
				{
					iActualValue+=iPageSpeed;
				}else {
					iActualValue-=iPageSpeed;
				}
			}else{
				if (sprtSlider.getPosition().x1>pt.x)
				{
					iActualValue-=iPageSpeed;
				}else {
					iActualValue+=iPageSpeed;
				}
			}
		}
	}

	if(iActualValue>iMaxValue)
		iActualValue=iMaxValue;
	if(iActualValue<iMinValue)
		iActualValue=iMinValue;

	btnUp.handleEvent(evt);
	btnDown.handleEvent(evt);
	if (!sprtSlider.handleEvent(evt))
		updateValue();
	UIHoverButton::handleEvent(evt);
	if (btnUp.getHoverStatus() || btnDown.getHoverStatus())
	{
		isHover=false;
	}
	return true;
}

bool UIScrollBar::paint(Image &backBuffer)
{
	positionElements();
	UIHoverButton::paint(backBuffer);
	btnUp.paint(backBuffer);
	btnDown.paint(backBuffer);
	sprtSlider.paint(backBuffer);
	return true;
}

void UIScrollBar::setSrcRect(Rect Up, Rect Down, Rect Slider, Rect Background)
{
	rctUp=Up;
	rctDown=Down;
	rctSlider=Slider;
	rctBack=Background;
	btnUp.setSrcRect(Up);
	btnDown.setSrcRect(Down);
	sprtSlider.setSrcRect(Slider);
	UIHoverButton::setSrcRect(Background);
	setHoverImage(HoverImage);

}

void UIScrollBar::setHoverImage(Image &imgHover)
{
	Image tmp;
	tmp.cloneImage(imgHover,rctUp);
	btnUp.setHoverImage(tmp);
	tmp.cloneImage(imgHover,rctDown);
	btnDown.setHoverImage(tmp);
	tmp.cloneImage(imgHover,rctBack);
	UIHoverButton::setHoverImage(tmp);
}


// Hier werden die Elemente positioniert.
// Dabei werden die seitlichen Buttons(btnUp/btnDown)
// genauso breit gemacht, wie hoch, aber als Maximum
// wird mit SCROLLBAR_MAX_SIZE eingesetzt.
// Natuerlich abhaengig von iScrollBarMode auch um 90 Grad gedreht...
void UIScrollBar::positionElements()
{
	int iButtonHeight;
	int iButtonWidth;
	if (iScrollBarMode==ALL2D_VERTICAL)
	{
		iButtonWidth=getPosition().x2;
		iButtonHeight=iButtonWidth;
		if (iButtonHeight>SCROLLBAR_MAX_SIZE)
			iButtonHeight=SCROLLBAR_MAX_SIZE;

		btnUp.setPosition(Rect(getPosition().x1, getPosition().y1,iButtonWidth,iButtonHeight));
		btnDown.setPosition(Rect(getPosition().x1, getPosition().y1+getPosition().y2-iButtonHeight,iButtonWidth,iButtonHeight));

		int ix,iy;
		ix=getPosition().x1;	// Vertikaler Slder ist an derselben X-Coordinate, wie der Scrollbar itself

		double pixelRange, valueRange, step;
		valueRange=(iMaxValue-iMinValue+iSliderSize);
		pixelRange=double(getPosition().y2-2*iButtonHeight);
		step=pixelRange/valueRange;

		iy= getPosition().y1 + getPosition().y2-iButtonHeight - (int)((iActualValue+iSliderSize-iMinValue)*step);
		if (!sprtSlider.isDragged())
			sprtSlider.setPosition(ix,iy,getPosition().x2,(int)(iSliderSize*step));

		Rect rctClipSlide=getPosition();
		rctClipSlide.y1+=iButtonHeight;
		rctClipSlide.x2=0;
		rctClipSlide.y2-=2*iButtonHeight+sprtSlider.getPosition().y2;
		sprtSlider.setClipRect(rctClipSlide);

	}else{
		iButtonHeight=getPosition().y2;
		iButtonWidth=iButtonHeight;
		if (iButtonWidth>SCROLLBAR_MAX_SIZE)
			iButtonWidth=SCROLLBAR_MAX_SIZE;

		btnDown.setPosition(Rect(getPosition().x1, getPosition().y1,iButtonWidth,iButtonHeight));
		btnUp.setPosition(Rect(getPosition().x1+getPosition().x2-iButtonWidth, getPosition().y1,iButtonWidth,iButtonHeight));

		int ix,iy;
		iy=getPosition().y1;	// Horizontaler Slider ist immer an derselben Y-Coordinate, wie der Scrollbar itself

		double pixelRange, valueRange, step;
		valueRange=(iMaxValue-iMinValue+iSliderSize);
		pixelRange=double(getPosition().x2-2*iButtonWidth);
		step=pixelRange/valueRange;

		ix= getPosition().x1 + iButtonWidth + (int)((iActualValue-iMinValue)*step);
		if (!sprtSlider.isDragged())
			sprtSlider.setPosition(ix,iy,(int)(iSliderSize*step),getPosition().y2);

		Rect rctClipSlide=getPosition();
		rctClipSlide.x1+=iButtonWidth;
		rctClipSlide.y2=0;
		rctClipSlide.x2-=2*iButtonWidth+sprtSlider.getPosition().x2;
		sprtSlider.setClipRect(rctClipSlide);
	}
}

string UIScrollBar::getName()
{
	return UIHoverButton::getName();
}
value UIScrollBar::getValue()
{
	return value("",iActualValue);
}
void UIScrollBar::setValue(value val)
{
	iActualValue=val.second;
}

void UIScrollBar::updateValue()
{
	double pixelRange, valueRange, step;
	int pixVal;

	if (getScrollBarMode()==ALL2D_VERTICAL)
	{
		pixVal=sprtSlider.getPosition().y1-sprtSlider.getOffset().y-getPosition().y1-btnUp.getPosition().y2;
		pixelRange=double(getPosition().y2-2*btnUp.getPosition().y2);
	}else{
		pixVal=sprtSlider.getPosition().x1-sprtSlider.getOffset().x-getPosition().x1-btnDown.getPosition().x2;
		pixelRange=double(getPosition().x2-2*btnUp.getPosition().x2);
	}

		valueRange=(iMaxValue-iMinValue+iSliderSize);
		step=valueRange/pixelRange;

	if (getScrollBarMode()==ALL2D_VERTICAL)
		iActualValue=iMaxValue-(step*pixVal);
	else
		iActualValue=iMinValue+(step*pixVal);

}

void UIScrollBar::setBlitMode(int bltMode)
{
	btnUp.setBlitMode(bltMode);
	btnDown.setBlitMode(bltMode);
	sprtSlider.setBlitMode(bltMode);
	UIHoverButton::setBlitMode(bltMode);
}

void UIScrollBar::setHoverBlitMode(int bltMode)
{
	btnUp.setHoverBlitMode(bltMode);
	btnDown.setHoverBlitMode(bltMode);
	UIHoverButton::setHoverBlitMode(bltMode);
}

void UIScrollBar::setPriority(int prio)
{
	btnUp.setPriority(prio);
	btnDown.setPriority(prio);
	sprtSlider.setPriority(prio);
	UIHoverButton::setPriority(prio);

}

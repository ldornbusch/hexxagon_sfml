// UIScrollBar.h: interface for the UIScrollBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UISCROLLBAR_H__02798592_3CE8_42AD_910D_CD00F26A1824__INCLUDED_)
#define AFX_UISCROLLBAR_H__02798592_3CE8_42AD_910D_CD00F26A1824__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIHoverButton.h"
#include "UIDragableSprite.h"
#include "hasValue.h"

#define ALL2D_HORIZONTAL  0x0002
#define ALL2D_VERTICAL	  0x0001

class UIScrollBar : public UIHoverButton, public hasValue   
{
public:
	string getName();
	value getValue();
	void setValue(value val);

	void setButtonProperties(int Max=100, int Min=0, int ButtonSpeed=1, int PageSpeed=20, int SliderSize=20);
	virtual void setPriority(int prio);
	virtual void setHoverBlitMode(int bltMode);
	virtual void setBlitMode(int bltMode);
	void setHoverImage(Image& imgHover);
	void setSrcRect(Rect Up=Rect(), Rect Down=Rect(), Rect Slider=Rect(), Rect Background=Rect());
	bool paint(Image& backBuffer);
	bool handleEvent(Event* evt);
	int getScrollBarMode();
	UIScrollBar(int iMode=ALL2D_VERTICAL);
	virtual ~UIScrollBar();

private:
	void setScrollBarMode(int iMode);
	void updateValue();
	int iMinValue,iMaxValue,iPageSpeed,iSliderSize,iButtonSpeed,iActualValue;
	void positionElements();
	int iScrollBarMode;
	Rect rctUp, rctDown, rctSlider, rctBack;
	UIHoverButton btnUp, btnDown;
	UIDragableSprite sprtSlider;
};

#endif // !defined(AFX_UISCROLLBAR_H__02798592_3CE8_42AD_910D_CD00F26A1824__INCLUDED_)

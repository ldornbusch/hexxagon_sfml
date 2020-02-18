// UIScrollBar.h: interface for the UIScrollBar class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UIHoverButton.h"
#include "UIDragableSprite.h"
#include "hasValue.h"

class UIScrollBar : public UIHoverButton, public hasValue
{
public:
    enum ScrollBar_Mode {
        HORIZONTAL,
        VERTICAL
    };
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
	ScrollBar_Mode getScrollBarMode();
	UIScrollBar(ScrollBar_Mode eMode=VERTICAL);
	virtual ~UIScrollBar();

private:
	void setScrollBarMode(ScrollBar_Mode eMode);
	void updateValue();
	int iMinValue,iMaxValue,iPageSpeed,iSliderSize,iButtonSpeed,iActualValue;
	void positionElements();
	ScrollBar_Mode eMode;
	Rect rctUp, rctDown, rctSlider, rctBack;
	UIHoverButton btnUp, btnDown;
	UIDragableSprite sprtSlider;
};

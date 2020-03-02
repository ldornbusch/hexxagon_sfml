// UIScrollArea.h: interface for the UIScrollArea class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2D/All2D_Base/xContainer.h"
#include "../All2D/All2D_Sprites/UISprite.h"
#include "UIScrollBar.h"
#include "hasValue.h"

class UIScrollArea : virtual public xContainer, virtual public UISprite, virtual public hasValue
{
public:
	bool	handleEvent(Event* evt);
	bool	paint(Image& backBuffer);
	void	setFont(ImageText& fnt);
	void	setImage(Image& pic);
	virtual void setName(string n);
	virtual string getName();
    virtual value getValue();
    void virtual setValue(value val);

	UIScrollArea();
	virtual ~UIScrollArea();

private:
	UISprite content;
	UIScrollBar vertical_Scroller;

};

// UIScrollArea.h: interface for the UIScrollArea class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "..\ALL2D\ALL2D_SPRITES\UISprite.h"
#include "hasValue.h"

class UIScrollArea : public UISprite , public hasValue
{
public:
	bool	handleEvent(Event* evt);
	bool	paint(Image& backBuffer);
	void	setFont(ImageText& fnt);
	string getName();
	void setValue(value val);
	value getValue();
	UIScrollArea();
	virtual ~UIScrollArea();

private:
	ImageText fntFont;

};

// UIButton.h: Schnittstelle für die Klasse UIButton.
// UIButton is a simple rectangle invisible button
// which sends a message when the mouse is pressed inside
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2D/All2D_Sprites/UIElement.h"

#define HOVER_ON		66666
#define HOVER_OFF		-66666

class UIButton : public virtual UIElement
{
public:
	void fire();
	virtual void leftClick();
	virtual void rightClick();
	virtual void setSendFlag(int i, unsigned int w=0, long l=0 );
	virtual bool getStatus();
	virtual bool handleEvent(Event* evt);
	UIButton();
	virtual ~UIButton();

protected:
	bool isClicked;
	int sendFlag;
	long sendLong;
	unsigned int sendWord;
};

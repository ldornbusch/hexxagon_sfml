// UIHoverButton.h: Schnittstelle für die Klasse UIHoverButton.
// UIHoverButton zeigt eines von zwei Bildern, je nachdem, ob die Mouse
// den Button beruehrt, oder nicht
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UIButton.h"
#include "../All2D/All2D_Sprites/UISprite.h"	// Hinzugefügt von der Klassenansicht

class UIHoverButton :
		public virtual UIButton,
		public virtual UISprite

{
public:
	virtual void setPosition(Rect rctPos);
	void setHoverStatus(bool blnFlag);
	void setHoverBlitMode(int ibltMode);
	void setHoverImage(Image& img);
	bool getHoverStatus();
	void setHoverFlag(int i, unsigned int w=0);// der letzte Wert gibt an, ob Hover In oder Hover Out
	int	 getHeight();
	int  getWidth();
	void init();
	virtual void setOffset(int x, int y);
	virtual void finish();
	virtual void setPriority(int prio);
	virtual void enter();
	virtual void leave();
	UIHoverButton();
	virtual ~UIHoverButton();
	bool handleEvent(Event *evt);
	bool paint(Image& Backbuffer);
protected:
	unsigned int hoverWord;
	int hoverFlag;
	long hoverLong;
	UISprite HoverImage;
	bool isHover;		// steht die Mouse über dem Button, oder nicht..
	int iHoverBltMode;
};

// GameMessageClass.h: interface for the GameMessageClass class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\Image.h"	// Added by ClassView

#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "GameImageCloner.h"
#include "..\ALL2DENGINE\GUI\UIHoverButton.h"	// Added by ClassView
#include "..\ALL2DENGINE\ALL2D\ALL2D_EVENTS\Event.h"	// Added by ClassView
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\ImageText.h"	// Added by ClassView
#include "KeyboardNavigator.h"	// Added by ClassView

class GameMessageBox :
	public xContainer
{
public:
	void setBackgroundColor(int iCol);
	void setPriority(int prio);
	void init();
	void setYesEvent(Event);
	void setMessage(string strText);
	void setYesButton(UIHoverButton& yes);
	void setNoButton(UIHoverButton& no);
	void setFont(ImageText& font);
	void activate(bool blnFlag);
	bool handleEvent(Event* evt);
	bool paint(Image& imgBackBuffer);
	GameMessageBox();
	virtual ~GameMessageBox();

private:
	int iBackGroundColor;
	void menuSelect();
	UIHoverButton& getMenuButton(int index);
	KeyboardNavigator KbdNavigator;
	ImageText TextFont;
	bool isVisible;
	UISprite sprtBackground;
	UISprite sprtTextBuffer;
	UIHoverButton btnNo;
	UIHoverButton btnYes;
	string strMessage;
};

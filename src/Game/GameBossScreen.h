// GameBossScreen.h: interface for the GameBossScreen class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "..\ALL2DENGINE\ALL2D\ALL2D_SPRITES\UIElement.h"
#include "GameImageCloner.h"

class GameBossScreen :	public UIElement,
						public GameImageCloner
{
public:
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	GameBossScreen();
	virtual ~GameBossScreen();
protected:
	Image imgFrameBuffer;
};

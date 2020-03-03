// GameBossScreen.h: interface for the GameBossScreen class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <All2D/All2DEngine/All2D/All2D_Sprites/UIElement.h>
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

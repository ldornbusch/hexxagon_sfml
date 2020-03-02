// GameTextScreen.h: interface for the GameTextScreen class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Base/xContainer.h"
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Added by ClassView
#include <string>

using std::string;

class GameTextScreen :
	public xContainer,
	public GameImageCloner
{
public:
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	GameTextScreen();
	virtual ~GameTextScreen();

private:
	string astrTextLines[20];
	ImageText TextFont;
};

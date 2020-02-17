// GameTextScreen.h: interface for the GameTextScreen class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "GameImageCloner.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\xContainer.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\ImageText.h"	// Added by ClassView
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

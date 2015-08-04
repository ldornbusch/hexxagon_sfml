// GameTextScreen.cpp: implementation of the GameTextScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "GameTextScreen.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameTextScreen::GameTextScreen() : xContainer("textscreen")
{

}

GameTextScreen::~GameTextScreen()
{

}

bool GameTextScreen::paint(Image& backBuffer)
{
	static float alpha=0.0;
	int xco,xco2,shadow,xOff;
	for (int x=0;x<20; x++)
	{
		shadow=-cos(alpha+(x*2*PI/20))*3+4;
		xco=cos(alpha+(x*2*PI/20))*5;
		xco2=sin(.5*alpha+(x*2*PI/20))*10;
		xOff=sin(.3*alpha)*5+5;

		if (astrTextLines[x]>"") {
			TextFont.PrintCenter(backBuffer,xco+shadow+70+20*x+xOff,astrTextLines[x].c_str(),IMAGE_BLTMODE_HALF,26,0,0,xco2+shadow);
			TextFont.PrintCenter(backBuffer,xco+70+20*x+xOff,astrTextLines[x].c_str(),IMAGE_BLTMODE_TRANS,26,0,0,xco2);
		}
		
	}
	alpha=alpha+.08;
	return true;
}

void GameTextScreen::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);

	TextFont.cloneImage(imgGFX,Rect(224,208,80,64));
	TextFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789:[]_@.-+*$%§!");
}

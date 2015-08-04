// GameBossScreen.cpp: implementation of the GameBossScreen class.
//
//////////////////////////////////////////////////////////////////////

#include "GameBossScreen.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameBossScreen::GameBossScreen()
{
	imgFrameBuffer.resize(640,480);

}

GameBossScreen::~GameBossScreen()
{
	imgFrameBuffer.finish();

}

void GameBossScreen::getGFX(Image& imgGFX)
{
	GameImageCloner::getGFX(imgGFX);
	imgElements.setSrcRect(Rect(0,960,640,480));
	imgElements.show(imgFrameBuffer,0,0,IMAGE_BLTMODE_FAST);
}

bool GameBossScreen::paint(Image& backBuffer)
{
	imgFrameBuffer.show(backBuffer,0,0,IMAGE_BLTMODE_FAST);
	return true;
}


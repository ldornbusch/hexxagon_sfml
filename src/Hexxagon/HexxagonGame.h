// HexxagonGame.h: interface for the HexxagonGame class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <All2D/All2DEngine/All2D/All2D_Base/xContainer.h>
#include <All2D/All2DEngine/All2D/All2D_Base/ImageText.h>
#include "../Game/GameImageCloner.h"
#include "HexxagonBoard.h"	// Added by ClassView
#include "HexxagonMove.h"	// Hinzugefügt von der Klassenansicht
#include "hexxagon_messages.h"
#include "hexxagonScore.h"	// Added by ClassView
#include "HexxagonState.h"	// Added by ClassView
#include "HexxagonAIPlayer.h"	// Added by ClassView
#include "Hexxagon3DPlayer.h"	// Hinzugefügt von der Klassenansicht

class HexxagonGame :	public xContainer,
						public GameImageCloner
{
public:
	bool isRunning();
	void suggestMove();
	void undoMove();
	int getState();
	void save(string strFileName);
	void load(string strFileName);
	HexxagonScore& getScore();
	HexxagonBoard& getBoard();
	bool paint(Image& backBuffer);
	void reset();
	void setBeginner(int i=HEX_RED_PLAYER);
	virtual bool handleEvent(Event* evt);
	void getGFX(Image& imgGFX);
	HexxagonGame();
	virtual ~HexxagonGame();
private:
	void printScore(Image& backBuffer);
	int update();
	HexxagonAIPlayer hexAI;
	Hexxagon3DPlayer hex3DPlayer;
	HexxagonScore scScore;
	HexxagonMove actualMove, suggestedMove;
	HexxagonBoard hexBoard;
	ImageText myFont;
	UISprite	sprtWinner;
	vector<int> vec2Flip;
	vector<HexxagonState*> vecMoves;
	int iSuggestTimeStart;		// when did the suggested Move started to show up
	int iBeginner;	// This is the player who will start the game
	int iGameStatus;
	int iPlayer;
protected:
	void unSuggest();
};

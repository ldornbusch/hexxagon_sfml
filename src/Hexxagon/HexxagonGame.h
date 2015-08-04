// HexxagonGame.h: interface for the HexxagonGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONGAME_H__39DCF96D_F5ED_4E77_8A18_31CDB21AB488__INCLUDED_)
#define AFX_HEXXAGONGAME_H__39DCF96D_F5ED_4E77_8A18_31CDB21AB488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GAME\GameImageCloner.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\xContainer.h"
#include "HexxagonBoard.h"	// Added by ClassView
#include "HexxagonMove.h"	// Hinzugefügt von der Klassenansicht
#include "Hexxagon_messages.h"
#include "hexxagonScore.h"	// Added by ClassView
#include "hexxagonState.h"	// Added by ClassView
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\ImageText.h"	// Added by ClassView
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

#endif // !defined(AFX_HEXXAGONGAME_H__39DCF96D_F5ED_4E77_8A18_31CDB21AB488__INCLUDED_)

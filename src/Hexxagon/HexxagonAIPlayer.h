// HexxagonAIPlayer.h: interface for the HexxagonAIPlayer class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "HexxagonStone.h"	// for the board reference
#include "HexxagonMove.h"		// for our best move

class HexxagonAIPlayer
{
public:
	HexxagonAIPlayer();
	virtual ~HexxagonAIPlayer();

	HexxagonMove getBestMove(int iPlayer, vector<HexxagonStone*> vecStones);

private:
	HexxagonMove analyze(int iIndex, vector<HexxagonStone*> vecStones);
	HexxagonMove bestMove;
	int iCurrentPlayer;
};

// HexxagonAIPlayer.h: interface for the HexxagonAIPlayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONAIPLAYER_H__8307EF68_EE2D_4321_AA5B_552FB3B43785__INCLUDED_)
#define AFX_HEXXAGONAIPLAYER_H__8307EF68_EE2D_4321_AA5B_552FB3B43785__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_HEXXAGONAIPLAYER_H__8307EF68_EE2D_4321_AA5B_552FB3B43785__INCLUDED_)

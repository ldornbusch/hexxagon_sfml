// HexxagonAIPlayer.cpp: implementation of the HexxagonAIPlayer class.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonAIPlayer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HexxagonAIPlayer::HexxagonAIPlayer() : bestMove()
{

}

HexxagonAIPlayer::~HexxagonAIPlayer()
{

}

HexxagonMove HexxagonAIPlayer::getBestMove(int iPlayer, vector<HexxagonStone*> vecStones)
{
	// remember current player
	iCurrentPlayer = iPlayer;

	// reset best move
	bestMove.Color		= iPlayer;
	bestMove.from			= -1;
	bestMove.to				= -1;
	bestMove.rate			= -1;
	bestMove.moveType	= -1;

	// loop through all stones
	for ( int x=0;x<vecStones.size();x++) {
		// analyze stone if it belongs to current player
		if ( vecStones[x]->getColor()==iCurrentPlayer) {
			HexxagonMove aiMove = analyze(x,vecStones);
			if ( aiMove.rate > bestMove.rate ) {
				bestMove = aiMove;
			}
		}
	}
  //xxagonMove bestMove = new HexxagonMove(iPlayer,iIndex,-1,0);
  return bestMove;

}

/*
 * analyse given stone and return best possible move
 * @param iIndex offset of the current stone in vector
 * @param vecStones vector of HexxagonStone*
 * @return HexxagonMove with the best rating
 * ===================================================================== */
HexxagonMove HexxagonAIPlayer::analyze(int iIndex, vector<HexxagonStone*> vecStones)
{
  // create new move and set to color and given index
	HexxagonMove ratedMove = HexxagonMove(vecStones[iIndex]->getColor(),iIndex,-1,-1,-1);
	
	// check all neighbouring stones
	for (int x=0; x<HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS;x++) {
		// get neighbour from current stone
		int iNeighbour = vecStones[iIndex]->getNeighbour(x);
		// if we have a neighbour and it is an empty field
		if (iNeighbour >= 0 && vecStones[iNeighbour]->getColor()==0) {
			// rate depending on move type
			int iRate = (x<HEX_NUM_STONE_NEIGHBOURS)?2:1;
			// check close neighbours of neighbours
			for (int y=0; y<HEX_NUM_STONE_NEIGHBOURS;y++) {
				// get close neighbour if it is valid
				int iSubNeighbour = vecStones[iNeighbour]->getNeighbour(y);
				// increment rate if field is sourrounded by enemy stones
				if ( iSubNeighbour>=0 
					&& (vecStones[iSubNeighbour]->getColor() != iCurrentPlayer)
					&& (vecStones[iSubNeighbour]->getColor() != 0))
					iRate++;
			}
			// compare rate with rate of last best rated move
			if ( iRate > ratedMove.rate ) {
				// copy rest of move attributes
				ratedMove.to			 = iNeighbour;
				ratedMove.rate		 = iRate;
				ratedMove.moveType = (x<HEX_NUM_STONE_NEIGHBOURS)?2:1;
			}
		}
	}
  
	// pass best possible move back
	return ratedMove;

}

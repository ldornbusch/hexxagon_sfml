// StonePositioner.h: Schnittstelle für die Klasse StonePositioner.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include "HexxagonStone.h"
using namespace std;

class StonePositioner
{
public:
	StonePositioner();
	virtual ~StonePositioner();
	void PositionStones(vector<HexxagonStone*> vecStones);
private:
	void initializeNeighbours(HexxagonStone* objStone, int iIndex, int iRow);
	bool isBlackOut(int iIndex);
	bool isInLine(int iIndex,int iRow);
};

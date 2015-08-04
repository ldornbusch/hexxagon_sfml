// StonePositioner.h: Schnittstelle für die Klasse StonePositioner.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STONEPOSITIONER_H__8B7ED7F2_3AA0_47BE_9120_741739EF77BC__INCLUDED_)
#define AFX_STONEPOSITIONER_H__8B7ED7F2_3AA0_47BE_9120_741739EF77BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_STONEPOSITIONER_H__8B7ED7F2_3AA0_47BE_9120_741739EF77BC__INCLUDED_)

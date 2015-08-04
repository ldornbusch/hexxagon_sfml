// HexxagonBoard.h: Schnittstelle für die Klasse HexxagonBoard.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONBOARD_H__CD9ACEF1_11BE_43AC_9573_42BEB0A6CCF7__INCLUDED_)
#define AFX_HEXXAGONBOARD_H__CD9ACEF1_11BE_43AC_9573_42BEB0A6CCF7__INCLUDED_

#include "hexxagonScore.h"	// Added by ClassView
#include "StonePositioner.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\GAME\GameImageCloner.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\xContainer.h"
#include "HexxagonStone.h"
#include "HexxagonMove.h"

class HexxagonBoard : 
	public xContainer, 
	public GameImageCloner  
{
public:
	vector<HexxagonMove> getPossibleMoves(int iColor);
	void updateScore(HexxagonScore& scScore);
	bool hiLight(int iIndex, bool hilite=true);
	void reset();
	int getColor(int iIndex);
	vector<int> processMove(HexxagonMove& mov);
	virtual void setVisible(int iIndex, bool blnVisible);
	vector<int> setColor(int iIndex, int iColor);
	void getGFX(Image &imgGFX);
	HexxagonBoard();
	virtual ~HexxagonBoard();
	vector<HexxagonStone*>& getStones();
private:
	StonePositioner positioner;
	// wenn ich einen "vector<HexxagonStone> vecStones;" benutze[keine Pointer] kann ich im destruktor nicht mehr mit delete die einzelnen Stones loeschen??
	vector<HexxagonStone*> vecStones;
};

#endif // !defined(AFX_HEXXAGONBOARD_H__CD9ACEF1_11BE_43AC_9573_42BEB0A6CCF7__INCLUDED_)

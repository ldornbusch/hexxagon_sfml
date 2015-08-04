// HexxagonMove.h: Schnittstelle für die Klasse HexxagonMove.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONMOVE_H__C266495B_83E3_4E82_A6E0_D97F420765C4__INCLUDED_)
#define AFX_HEXXAGONMOVE_H__C266495B_83E3_4E82_A6E0_D97F420765C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class HexxagonMove
{
public:
	int rate;
	int moveType;
	int Color;
	int to;
	int from;
	HexxagonMove();
	HexxagonMove(int iColor, int iFrom, int iTo, int iRate, int iMoveType);
	virtual ~HexxagonMove();
	HexxagonMove& operator=(HexxagonMove move);

};

#endif // !defined(AFX_HEXXAGONMOVE_H__C266495B_83E3_4E82_A6E0_D97F420765C4__INCLUDED_)

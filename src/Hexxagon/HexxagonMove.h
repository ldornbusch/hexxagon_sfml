// HexxagonMove.h: Schnittstelle für die Klasse HexxagonMove.
//
//////////////////////////////////////////////////////////////////////
#pragma once

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

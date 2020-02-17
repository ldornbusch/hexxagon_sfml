// HexxagonMove.cpp: Implementierung der Klasse HexxagonMove.
//
//////////////////////////////////////////////////////////////////////

#include "HexxagonMove.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

HexxagonMove::HexxagonMove()
{
	from=-1;
	to=-1;
	moveType=-1;
	rate=-1;
}

HexxagonMove::HexxagonMove(int iColor, int iFrom, int iTo, int iRate, int iMoveType)
{
	Color		= iColor;
	from		= iFrom;
	to			= iTo;
	rate		= iRate;
	moveType= iMoveType;
}

HexxagonMove& HexxagonMove::operator=(HexxagonMove move)
{
	Color		= move.Color;
	from		= move.from;
	to			= move.to;
	rate		= move.rate;
	moveType= move.moveType;
	return *this;
}

HexxagonMove::~HexxagonMove()
{

}

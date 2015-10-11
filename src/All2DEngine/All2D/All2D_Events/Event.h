// Event.h: Schnittstelle f�r die Klasse Event.
// Das Event wird der handleEvent Funktion �bergeben...
// Es besteht aus einem Type, und zwei 32-Bit Werten mit Daten..
// zB MouseMove, Drag, X/Y Coords, TastenDruck usw.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../includes/gameMessages.h"
class Event
{
public:
	Event(unsigned int type,unsigned int wDat, long lDat);
	virtual ~Event();
	unsigned int Type;
	unsigned int wData;
	long lData;
	unsigned int iTimeCode;
};

// Event.h: Schnittstelle für die Klasse Event.
// Das Event wird der handleEvent Funktion übergeben...
// Es besteht aus einem Type, und zwei 32-Bit Werten mit Daten..
// zB MouseMove, Drag, X/Y Coords, TastenDruck usw.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENT_H__A1412741_5C1B_44B9_AC82_121FE3394FB5__INCLUDED_)
#define AFX_EVENT_H__A1412741_5C1B_44B9_AC82_121FE3394FB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_EVENT_H__A1412741_5C1B_44B9_AC82_121FE3394FB5__INCLUDED_)

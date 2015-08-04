// ControllerAdapter.h: Schnittstelle für die Klasse ControllerAdapter.
// Basisklasse fuer die verschiedenen Controller-Arten:
// -Mouse   ...done 10.12.02
// -KeySet I...done 10.12.02
// -KeySet II
// -AI(Computer steuert)...done 11.12.02
// -TCP/IP-Netzwerkspiel
// Der ControllerAdapter ist die Abstrakte Basisklasse fuer die 
// verschiedenenSteuerungsmoeglichkeiten des MousePfeils. Sie werden
// Alle von HexxagonGameController instanziert und dann die beiden 
// aktiven Controller per Pointer an den HexxagonMouseMover uebergeben.
// The Methods sollen folgendes tun:
//
//	virtual void generateEvent();
//  Diese Methode soll in der paint()-Methode des Parents aufgerufen werden,
//  Um eine Moeglichkeit zu schaffen, eigenstaendig neue Messages zu generieren, 
//  da handleEvent nur zur Transformation bestehender Events benutzt werden kann.
//  So wird damit zB. die Mausbewegung ueber die Tastatur emuliert, da ansonsten nur die 
//  betriebssysteminterne Tastenwiederhohlung eine sehr ruckelige Moeglichkeit der
//  Bewegung bieten wuerder
//
//	virtual bool handleEvent(Event* evt);
//  Diese Methode reagiert auf die Messages und filtert evt. ungewünschte Messages 
//  aus(z.B MouseMoves der Mouse, wenn man mit Tastatur steuern moechte)
//
//	virtual Rect getPosition();
//  gibt die Position des MousePointers wieder
//
//  virtual pause(bool start=false);
//  merkt sich eingehende Events(bei TCPIP aber wandelt diese nicht um)
//  erst wenn die Pause wieder aufgehoben wird, werden die Events abgehandelt
//  (notwendig, um das Menu auch bei zwei Computerspielern aufzurufen..)
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLLERADAPTER_H__89FC572E_155E_44C8_BC8F_ACE7ED8BC3B8__INCLUDED_)
#define AFX_CONTROLLERADAPTER_H__89FC572E_155E_44C8_BC8F_ACE7ED8BC3B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ALL2DENGINE\ALL2D\ALL2D_Events\Event.h"
#include "..\ALL2DENGINE\UTILS\Rect.h"	// Hinzugefügt von der Klassenansicht


class ControllerAdapter  
{
public:
	virtual void generateEvent() =0;
	virtual bool handleEvent(Event* evt)=0;
	virtual Rect getPosition() =0;
	virtual void pause(bool start=false)=0;
	ControllerAdapter(){};
	virtual ~ControllerAdapter(){};
};

#endif // !defined(AFX_CONTROLLERADAPTER_H__89FC572E_155E_44C8_BC8F_ACE7ED8BC3B8__INCLUDED_)

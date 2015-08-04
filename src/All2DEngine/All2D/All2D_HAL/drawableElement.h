// drawableElement.h: Schnittstelle für die Klasse drawableElement.
// abstrakte Basisklasse um All2D Anwendungen auf den Bildschirm 
// zu bringen..
// eine abgeleitete Klasse muss
// paint (CBitMap* Buffer, int tics)	(Zeichnen des BildschirmInhalts) und 
// handleEvent(Event* evt)				(Behandlung von WindowMessages)	
// definieren..
//
//////////////////////////////////////////////////////////////////////

#if !defined PI
#define PI 3.1428
#endif

#if !defined(AFX_DEMO_H__843D4131_84C1_11D3_B8B2_0000E8699C86__INCLUDED_)
#define AFX_DEMO_H__843D4131_84C1_11D3_B8B2_0000E8699C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2D_Events/Event.h"
#include "Bitmap.h"

class drawableElement
{
public:
	virtual int getID();
	virtual void finish();
    virtual void init();
	drawableElement();
	virtual ~drawableElement();
private:
	void getNewID();
	static int uniqueIDCounter;
	int uniqueID;
protected:
	bool isInitialized;
};


#endif // !defined(AFX_DEMO_H__843D4131_84C1_11D3_B8B2_0000E8699C86__INCLUDED_)

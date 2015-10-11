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

#pragma once

#include "../All2D_Events/Event.h"
#include "Bitmap.h"

class drawableElement
{
public:
	virtual unsigned int getID();
	virtual void finish();
    virtual void init();
	drawableElement();
	virtual ~drawableElement();
private:
	void getNewID();
	static int uniqueIDCounter;
	unsigned int uniqueID;
protected:
	bool isInitialized;
};

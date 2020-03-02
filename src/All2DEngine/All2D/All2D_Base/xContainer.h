// xModule.h: Schnittstelle für die Klasse xModule.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "xElement.h"
#include "Image.h"
#include <string>
#include <vector>
// For Standard TemplateLibrary Support...
using std::string;

/*
	xContainer enthaelt einfach nur eine Menge xElements und kann diese per Name oder ID einfach Löschen
	Messages wie auch paints werden automatisch an alle ContainerInsassen weitergeleitet.
	die Methoden init(), finish(), load() und unload() werden zum asynchronen Bilderladen per PicLoader benutzt
	load() meldet seine benötigten Ressourcen beim PicLoader an..
	AENDERUNG: frueher wurde der Konstruktor benutzt
	dies ist aber aufgrund der static Members im ApplicationModule nicht mehr möglich..
	init() kann dann diese Bilder laden(sind vorher vom Picloader geladen worden)
	finish() kann die Bilder wieder freigeben
	unload() wird im Moment nicht benutzt

*/

class xContainer : public xElement
{
public:
	virtual void deleteElements();	// loescht die Elements und gibt den Speicher wieder frei
	int add(xElement&comp, unsigned int insertAt);
	virtual void init();		// diese Methode wird benutzt, um ressourcen beim Picloader zu laden und zu initialisieren
	virtual void finish();		// diese Methode wird benutzt, um Objecte zu deinitialisieren
	virtual void requestLoad();		// diese Function wird benutzt, um Ressourcen beim PicLoader anzumelden
	virtual bool paint(Image& img);				// And Calls this Paint with the Image backBufferImage
	virtual bool handleEvent(Event * evt);
	void remove(xElement& component);							//This will be removed by Components Name
	void remove(unsigned int compHandle);							//This will be removed by Components Handle
	int add(xElement& comp, bool insertAtEnd=true);			// Gives back the Handle of the added xModule
// Construction/Destruction
	xContainer(string n);
	virtual ~xContainer();
protected:
	vector<xElement*> modules;	// muss ein Zeiger sein, wg. virtuellen Funktionen
};

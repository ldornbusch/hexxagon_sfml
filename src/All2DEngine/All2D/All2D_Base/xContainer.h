// xModule.h: Schnittstelle f�r die Klasse xModule.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMODULE_H__BD24C301_F92B_11D4_B046_00E098802DF2__INCLUDED_)
#define AFX_XMODULE_H__BD24C301_F92B_11D4_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "xElement.h"
#include "Image.h"
#include <String>
#include <Vector>
// For Standard TemplateLibrary Support...
using namespace std;

/*
	xContainer enthaelt einfach nur eine Menge xElements und kann diese per Name oder ID einfach L�schen
	Messages wie auch paints werden automatisch an alle ContainerInsassen weitergeleitet.
	die Methoden init(), finish(), load() und unload() werden zum asynchronen Bilderladen per PicLoader benutzt
	load() meldet seine ben�tigten Ressourcen beim PicLoader an..
	AENDERUNG: frueher wurde der Konstruktor benutzt
	dies ist aber aufgrund der static Members im ApplicationModule nicht mehr m�glich..
	init() kann dann diese Bilder laden(sind vorher vom Picloader geladen worden)
	finish() kann die Bilder wieder freigeben
	unload() wird im Moment nicht benutzt

*/

class xContainer : public xElement
{
public:
	virtual void deleteElements();	// loescht die Elements und gibt den Speicher wieder frei
	int add(xElement&comp, int insertAt);
	virtual void init();		// diese Methode wird benutzt, um ressourcen beim Picloader zu laden und zu initialisieren
	virtual void finish();		// diese Methode wird benutzt, um Objecte zu deinitialisieren
	virtual void requestLoad();		// diese Function wird benutzt, um Ressourcen beim PicLoader anzumelden
	virtual bool paint(Image& img);				// And Calls this Paint with the Image backBufferImage
	virtual bool handleEvent(Event * evt);
	void remove(xElement& component);							//This will be removed by Components Name
	void remove(int compHandle);							//This will be removed by Components Handle
	int add(xElement& comp, bool insertAtEnd=true);			// Gives back the Handle of the added xModule
// Construction/Destruction
	xContainer(string n);
	virtual ~xContainer();
protected:
	vector<xElement*> modules;	// muss ein Zeiger sein, wg. virtuellen Funktionen
};

#endif // !defined(AFX_XMODULE_H__BD24C301_F92B_11D4_B046_00E098802DF2__INCLUDED_)

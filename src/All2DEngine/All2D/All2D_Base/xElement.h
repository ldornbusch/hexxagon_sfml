// xElement.h: Schnittstelle f�r die Klasse xElement.
/*
 In dieser Klasse findet die Anbindung/ Uebersetzung an die All2D Engine statt..
 statt eines CBMText wird ein Paint in der Routine benutzt, bzw. automatisch �bersetzt
 in saemtlichen oberen Klassen wird dann mit Images gearbeitet
*/

//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2D_HAL/drawableElement.h"
#include "Image.h"
#include <string>
// For Standard TemplateLibrary Support...
using std::string;

class xElement : public drawableElement
{
public:
	virtual bool paint(Image& img);
	virtual bool handleEvent(Event* evt);
	virtual void requestLoad();		// diese Function wird benutzt, um Ressourcen beim PicLoader anzumelden
	virtual void notify(Event evt);
	xElement(string n);
	xElement();
	virtual ~xElement();
	void setName(string n);
	string getName();
private:
	string name;
protected:
};

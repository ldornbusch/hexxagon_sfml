// xElement.h: Schnittstelle f�r die Klasse xElement.
/*
 In dieser Klasse findet die Anbindung/ Uebersetzung an die All2D Engine statt..
 statt eines CBMText wird ein Paint in der Routine benutzt, bzw. automatisch �bersetzt
 in saemtlichen oberen Klassen wird dann mit Images gearbeitet
*/

//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XELEMENT1_H__A7B2AB59_C506_4775_AC81_23F8ACB111C3__INCLUDED_)
#define AFX_XELEMENT1_H__A7B2AB59_C506_4775_AC81_23F8ACB111C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../ALL2D_HAL/drawableElement.h"
#include "Image.h"
#include <String>
// For Standard TemplateLibrary Support...
using namespace std;

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

#endif // !defined(AFX_XELEMENT1_H__A7B2AB59_C506_4775_AC81_23F8ACB111C3__INCLUDED_)

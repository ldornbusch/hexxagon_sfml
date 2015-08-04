// xElement1.cpp: Implementierung der Klasse xElement.
//
//////////////////////////////////////////////////////////////////////

#include "xElement.h"


bool xElement::paint(Image& img) 
{
	return true;
}
bool xElement::handleEvent(Event* evt)
{
	return true;
}
void	xElement::notify(Event evt)
{
}
	//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

xElement::xElement(string n) : name(n)
{

}

xElement::xElement() : name("")
{

}

xElement::~xElement()
{

}

void xElement::setName(string n)
{
//	if (name=="")	// eigentlich sollte der name nur einmal gesetzt werden und danach versiegelt werden...20.06.2001
		name=n;
}

// diese Function wird benutzt, um Ressourcen beim PicLoader anzumelden
void xElement::requestLoad()
{

}

string xElement::getName()
{
	return name;
}

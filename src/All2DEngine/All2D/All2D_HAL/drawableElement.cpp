// drawableElement.cpp: Implementierung der Klasse drawableElement.//
// drawableElement Klasse als Basisklasse für alle All2D-Applikationen
//
//////////////////////////////////////////////////////////////////////

#include "drawableElement.h"

int drawableElement::uniqueIDCounter =0;

/////////////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
/////////////////////////////////////////////////////////////////////////////

drawableElement::drawableElement()
{
	isInitialized=false;
	getNewID();
}
/////////////////////////////////////////////////////////////////////////////
drawableElement::~drawableElement()
{
}

// Private Routine for ID Managing..
void drawableElement::getNewID()
{
	uniqueID = uniqueIDCounter++;
}

// This method initializes the Element..
void drawableElement::init()
{
	isInitialized=true;
}

// This method De-initializes the Element..
void drawableElement::finish()
{
	isInitialized=false;
}

unsigned int drawableElement::getID()
{
	return uniqueID;
}

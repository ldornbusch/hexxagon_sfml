// xModule.cpp: Implementierung der Klasse xContainer.
//
//////////////////////////////////////////////////////////////////////

#include "xContainer.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

xContainer::xContainer(string n) : xElement(n)
{
}

xContainer::~xContainer()
{
	modules.clear();
}

int xContainer::add(xElement& comp, bool insertAtEnd)
{
	if (insertAtEnd)
		modules.insert(modules.end(), &comp);
	else
		modules.insert(modules.begin(), &comp);
	return comp.getID();
}

int xContainer::add(xElement &comp, unsigned int insertAt)
{
	if (insertAt<modules.size())
	{
		vector<xElement*>::iterator ilt=modules.begin()+ insertAt;
		modules.insert( ilt,&comp);
	} else {
		add(comp);
	}
	return comp.getID();
}
// TODO:noch nicht implementiert... wie wird das Object,
// welches zu entfernen ist angegeben?
// Über den Namen?
void xContainer::remove(xElement& compName)
{
	remove(compName.getID());
}
void xContainer::remove(unsigned int compHandle)
{
	for (vector<xElement*>::iterator x=modules.begin(); x!=modules.end();x++)
		if ((*x)->getID()==compHandle)
		{
			modules.erase(x);
			break;
		}
}

bool xContainer::handleEvent(Event *evt)
{
	bool retVal;

	for ( int x=modules.size()-1; x>-1;x--)
//	for ( int x=0; x<modules.size();x++)
	{
		retVal=modules[x]->handleEvent(evt);
		if (retVal==false)
			break;
	}
	return retVal;
}
bool xContainer::paint(Image& img)
{
	for (vector<xElement*>::iterator x=modules.begin();x!=modules.end();x++)
		(*x)->paint(img);
	return true;
}


// diese Methode wird benutzt, um ressourcen beim Picloader zu laden und zu initialisieren
void xContainer::init()
{

}

// diese Methode wird benutzt, um Objecte zu deinitialisieren
void xContainer::finish()
{
	for (vector<xElement*>::iterator x=modules.begin();x!=modules.end();x++)
	{
		if ((*x)->getName()!="saveIcons[0]")	// TODO wieder raus..Picloader uebernimmt RessourcenVerwaltung..
			(*x)->finish();
	}

	modules.clear();

	isInitialized=false;
}

// diese Function wird benutzt, um Ressourcen beim PicLoader anzumelden
void xContainer::requestLoad()
{
	for (vector<xElement*>::iterator x=modules.begin();x!=modules.end();x++)
		(*x)->requestLoad();

}

// loescht die Elements und gibt den Speicher wieder frei
void xContainer::deleteElements()
{
	for (vector<xElement*>::iterator x=modules.begin();x!=modules.end();x++)
		delete (*x);

	modules.clear();
}

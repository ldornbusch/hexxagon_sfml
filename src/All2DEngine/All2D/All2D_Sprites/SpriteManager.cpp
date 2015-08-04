// BlitManager.cpp: Implementierung der Klasse BlitManager.
//
//////////////////////////////////////////////////////////////////////

#include "SpriteManager.h"
#include "../All2D_System.h"
#include <algorithm>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SpriteManager::SpriteManager(): vecEntries(),
										 	BackgroundBuffer()
{
}

SpriteManager::~SpriteManager()
{

}

/**
Loescht den Vector mit den Sprites, fuer naechstes Frame
*/
void SpriteManager::clear()
{
	for (vector<SpriteEntry*>::iterator x= vecEntries.begin();x!=vecEntries.end(); x++)
	{
		delete(*x);
	}
	vecEntries.clear();
}

// In richtiger Reihenfolge alle Malen...
void SpriteManager::paint(Image& BackBuffer)
{
	stable_sort(vecEntries.begin(),vecEntries.end(),SpriteEntry());
	for (vector<SpriteEntry*>::iterator x= vecEntries.begin();x!=vecEntries.end(); x++)
	{
		((*x)->sprite)->blit(BackBuffer, (*x)->BlitMode);
	}
}

void SpriteManager::add(SpriteEntry *sp)
{
	vecEntries.insert(vecEntries.end(),sp);
}


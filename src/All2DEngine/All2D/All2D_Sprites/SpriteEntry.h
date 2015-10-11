// BlitEntry.h: Schnittstelle f�r die Klasse BlitEntry.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "UISprite.h"	// Hinzugef�gt von der Klassenansicht

class SpriteEntry
{
public:
	SpriteEntry(UISprite* sprite, int prio, int bltMode);
	SpriteEntry();
	~SpriteEntry();
	int BlitMode;
	int Priority;
	UISprite*	sprite;
	bool operator() (const SpriteEntry* s1, const SpriteEntry* s2)	// Sortieren der SpriteEntrys
	{
		return ((s1)->Priority < (s2)->Priority);
	}
};

// SpriteEntry.cpp: Implementierung der Klasse SpriteEntry.
//
//////////////////////////////////////////////////////////////////////

#include "SpriteEntry.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

SpriteEntry::SpriteEntry(UISprite* uiSprite, int prio, int bltMode)
{
	sprite=uiSprite;
	Priority=prio;
	BlitMode=bltMode;
}

SpriteEntry::SpriteEntry()
{
}

SpriteEntry::~SpriteEntry()
{
}
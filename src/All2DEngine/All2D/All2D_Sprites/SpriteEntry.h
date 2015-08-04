// BlitEntry.h: Schnittstelle für die Klasse BlitEntry.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLITENTRY_H__721EB675_B7CF_4D79_A695_DDC7FFEC7629__INCLUDED_)
#define AFX_BLITENTRY_H__721EB675_B7CF_4D79_A695_DDC7FFEC7629__INCLUDED_

#include "UISprite.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_BLITENTRY_H__721EB675_B7CF_4D79_A695_DDC7FFEC7629__INCLUDED_)

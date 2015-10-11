// BlitManager.h: Schnittstelle f�r die Klasse BlitManager.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
using namespace std;

#include "UISprite.h"
#include "SpriteEntry.h"
#include "../../UTILS\POINT.H"	// Hinzugef�gt von der Klassenansicht
#include "../../UTILS\Rect.h"	// Hinzugef�gt von der Klassenansicht

class SpriteManager
{
public:

	bool isDoubleBuffering();
	void add(SpriteEntry* sp);
	void paint(Image& BackBuffer);
	void clear();
	SpriteManager();
	virtual ~SpriteManager();
private:
	vector<SpriteEntry*> vecEntries;
	Image BackgroundBuffer;
protected:

};

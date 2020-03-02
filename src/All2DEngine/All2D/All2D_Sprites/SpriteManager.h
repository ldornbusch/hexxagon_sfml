// BlitManager.h: Schnittstelle für die Klasse BlitManager.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
using std::vector;

#include "UISprite.h"
#include "SpriteEntry.h"
#include "../../Utils/Point.h"	// Hinzugefügt von der Klassenansicht
#include "../../Utils/Rect.h"	// Hinzugefügt von der Klassenansicht

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

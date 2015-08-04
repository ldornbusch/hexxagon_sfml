// BlitManager.h: Schnittstelle für die Klasse BlitManager.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLITMANAGER_H__939D9A6E_864F_49D2_B62D_0801C6C42979__INCLUDED_)
#define AFX_BLITMANAGER_H__939D9A6E_864F_49D2_B62D_0801C6C42979__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "UISprite.h"
#include "SpriteEntry.h"
#include "../../UTILS\POINT.H"	// Hinzugefügt von der Klassenansicht
#include "../../UTILS\Rect.h"	// Hinzugefügt von der Klassenansicht

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

#endif // !defined(AFX_BLITMANAGER_H__939D9A6E_864F_49D2_B62D_0801C6C42979__INCLUDED_)

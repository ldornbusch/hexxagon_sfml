// GameImageCloner.h: Schnittstelle für die Klasse GameImageCloner.
// A Small Class with the Method getGFX(Image*gfxElements)
// For cloning the GraficElements..
// So they are inside any Object wich will need it
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLUMNSIMAGECLONER_H__4BB56F93_7BC7_4DB1_9D28_F0C27EB7A29D__INCLUDED_)
#define AFX_COLUMNSIMAGECLONER_H__4BB56F93_7BC7_4DB1_9D28_F0C27EB7A29D__INCLUDED_

#include "../All2DEngine/All2D/All2D_Base\Image.h"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GameImageCloner  
{
public:
	virtual void getGFX(Image& imgGFX);
	GameImageCloner();
	virtual ~GameImageCloner();

protected:
	Image imgElements;
};

#endif // !defined(AFX_COLUMNSIMAGECLONER_H__4BB56F93_7BC7_4DB1_9D28_F0C27EB7A29D__INCLUDED_)

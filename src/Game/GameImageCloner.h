// GameImageCloner.h: Schnittstelle für die Klasse GameImageCloner.
// A Small Class with the Method getGFX(Image*gfxElements)
// For cloning the GraficElements..
// So they are inside any Object wich will need it
//////////////////////////////////////////////////////////////////////

#pragma once

#include <All2D/All2DEngine/All2D/All2D_Base/Image.h>

class GameImageCloner
{
public:
	virtual void getGFX(Image& imgGFX);
	GameImageCloner();
	virtual ~GameImageCloner();

protected:
	Image imgElements;
};

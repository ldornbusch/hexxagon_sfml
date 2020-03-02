// GamePit.h: Schnittstelle für die Klasse GamePit.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"
#include "../All2DEngine/All2D/All2D_Base/Image.h"	// Hinzugefügt von der Klassenansicht

class GamePit  :	public UIElement
{
public:
	virtual void setStone(int x, int y, int value)=0;
	virtual bool isFree(int x, int y)=0;
	virtual void emptyPit()=0;
	GamePit();
	virtual ~GamePit();

};

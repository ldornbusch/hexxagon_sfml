// HexxagonStone.h: Schnittstelle für die Klasse HexxagonStone.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2DEngine/Gui/UIHoverButton.h"
#include "../Game/GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Sprites/UISprite.h"	// Added by ClassView
#include "hexxagon_messages.h"

class HexxagonStone : public UIHoverButton , GameImageCloner
{
public:
	virtual bool handleEvent(Event* evt);
	void setLook();
	void setState(int iState);
	int isNeighbour(int iIndex);
	int getNeighbour(int iDirection);
	void setNeighbour(int iDirection,int iIndex);
	virtual bool paint(Image& backBuffer);
	virtual bool isInside(int x, int y);
	void getGFX(Image& imgGFX);
	HexxagonStone(int id);
	virtual ~HexxagonStone();
	unsigned int getID();
	int getColor();
	void setColor(int iCol);
	void reset();
private:
	UISprite Hut;
	static UISprite** imgStoneImages;
	int Neighbours[HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS];
	unsigned int ID;
	int iColor;
	int	iButtonState;

};

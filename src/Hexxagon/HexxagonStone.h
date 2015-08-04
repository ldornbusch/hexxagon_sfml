// HexxagonStone.h: Schnittstelle f�r die Klasse HexxagonStone.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HEXXAGONSTONE_H__2318438B_E0F1_43A2_978F_DA4719BBFBBF__INCLUDED_)
#define AFX_HEXXAGONSTONE_H__2318438B_E0F1_43A2_978F_DA4719BBFBBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ALL2DENGINE\GUI\UIHoverButton.h"
#include "..\game\GameImageCloner.h"
#include "Hexxagon_messages.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_SPRITES\UISprite.h"	// Added by ClassView

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
	int getID();
	int getColor();
	void setColor(int iCol);
	void reset();
private:
	UISprite Hut;
	static UISprite** imgStoneImages;
	int Neighbours[HEX_NUM_STONE_NEIGHBOURS+HEX_NUM_STONE_DISTANT_NEIGHBOURS];
	int ID;
	int iColor;
	int	iButtonState;

};

#endif // !defined(AFX_HEXXAGONSTONE_H__2318438B_E0F1_43A2_978F_DA4719BBFBBF__INCLUDED_)
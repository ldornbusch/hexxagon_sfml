// GameBossScreen.h: interface for the GameBossScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEBOSSSCREEN_H__E9C951B6_C64D_4344_8E4D_BD1EC0F20A35__INCLUDED_)
#define AFX_GAMEBOSSSCREEN_H__E9C951B6_C64D_4344_8E4D_BD1EC0F20A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ALL2DENGINE\ALL2D\ALL2D_SPRITES\UIElement.h"
#include "GameImageCloner.h"

class GameBossScreen :	public UIElement,
						public GameImageCloner
{
public:
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	GameBossScreen();
	virtual ~GameBossScreen();
protected:
	Image imgFrameBuffer;
};

#endif // !defined(AFX_GAMEBOSSSCREEN_H__E9C951B6_C64D_4344_8E4D_BD1EC0F20A35__INCLUDED_)

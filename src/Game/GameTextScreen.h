// GameTextScreen.h: interface for the GameTextScreen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMETEXTSCREEN_H__782FE551_BEA0_48B1_80C4_F8171B4C4D0D__INCLUDED_)
#define AFX_GAMETEXTSCREEN_H__782FE551_BEA0_48B1_80C4_F8171B4C4D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameImageCloner.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\xContainer.h"
#include "..\ALL2DENGINE\ALL2D\ALL2D_BASE\ImageText.h"	// Added by ClassView
#include <string>

using namespace std;

class GameTextScreen : 
	public xContainer, 
	public GameImageCloner  
{
public:
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	GameTextScreen();
	virtual ~GameTextScreen();

private:
	string astrTextLines[20];
	ImageText TextFont;
};

#endif // !defined(AFX_GAMETEXTSCREEN_H__782FE551_BEA0_48B1_80C4_F8171B4C4D0D__INCLUDED_)

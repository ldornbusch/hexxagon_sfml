// GameHighScore.h: Schnittstelle für die Klasse GameHighScore.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEHIGHSCORE_H__24287676_E2D4_47C6_9EF5_31D4DCB80D42__INCLUDED_)
#define AFX_GAMEHIGHSCORE_H__24287676_E2D4_47C6_9EF5_31D4DCB80D42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"
#include "GameImageCloner.h"

#include <String>
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugefügt von der Klassenansicht

using namespace std;

#define HIGH_SCORE_ENTRIES		10

class GameHighScore : 
	public UIElement, 
	public GameImageCloner  
{
public:
	void insert(string strName, int iPts);
	int getPlace(int iPts);
	void getGFX(Image& imgGFX);
	void load();
	void save();
	bool paint(Image& backBuffer);
	GameHighScore();
	virtual ~GameHighScore();
private:
	ImageText TextFont;
	string strNames[HIGH_SCORE_ENTRIES];
	int		iPoints[HIGH_SCORE_ENTRIES];
};

#endif // !defined(AFX_GAMEHIGHSCORE_H__24287676_E2D4_47C6_9EF5_31D4DCB80D42__INCLUDED_)

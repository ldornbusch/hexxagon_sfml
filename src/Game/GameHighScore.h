// GameHighScore.h: Schnittstelle f�r die Klasse GameHighScore.
//
//////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

#include <All2D/All2DEngine/All2D/All2D_Sprites/UIElement.h>
#include <All2D/All2DEngine/All2D/All2D_Base/ImageText.h>

#include "GameImageCloner.h"

using std::string;

#define HIGH_SCORE_ENTRIES		10

class GameHighScore :
	public UIElement,
	public GameImageCloner
{
public:
	void insert(string strName, long int iPts);
	int getPlace(long int iPts);
	void getGFX(Image& imgGFX);
	void load();
	void save();
	bool paint(Image& backBuffer);
	GameHighScore();
	virtual ~GameHighScore();
private:
	ImageText TextFont;
	string strNames[HIGH_SCORE_ENTRIES];
	long int		iPoints[HIGH_SCORE_ENTRIES];
};

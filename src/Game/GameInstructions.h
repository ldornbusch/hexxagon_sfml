// GameInstructions.h: Schnittstelle f�r die Klasse GameInstructions.
// This Class handles the Credits and the Help Texts
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugef�gt von der Klassenansicht
#include "GameImageCloner.h"
#include "../All2DEngine/All2D/All2D_Sprites/UIElement.h"

class GameInstructions : public UIElement,
						 public GameImageCloner
{
public:
	void setCredit(bool blnFlag);
	void getGFX(Image& imgGFX);
	bool paint(Image& backBuffer);
	GameInstructions();
	virtual ~GameInstructions();
private:
	bool blnShowCredit;
	ImageText TextFont;
	static char CreditMessage[];
	static char HelpMessage[];

};


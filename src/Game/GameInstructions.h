// GameInstructions.h: Schnittstelle für die Klasse GameInstructions.
// This Class handles the Credits and the Help Texts
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEINSTRUCTIONS_H__C12DC579_D209_40EA_B4DA_600FF2308872__INCLUDED_)
#define AFX_GAMEINSTRUCTIONS_H__C12DC579_D209_40EA_B4DA_600FF2308872__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/All2D_Base/ImageText.h"	// Hinzugefügt von der Klassenansicht
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

#endif // !defined(AFX_GAMEINSTRUCTIONS_H__C12DC579_D209_40EA_B4DA_600FF2308872__INCLUDED_)

// HexxagonGameController.h: Schnittstelle für die Klasse HexxagonGameController.
// Handelt das Spiel als gesamtes:
// Start Bildschirm, Instruktions, HighScore usw
// Nicht zu verwechseln mit den ControllerAdaptern, die fuer die Uebersetzung der Steuerung notwendig sind
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALLERGAMECONTROLLER_H__42480621_C0F3_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_BALLERGAMECONTROLLER_H__42480621_C0F3_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2DEngine/All2D/AppGameController.h"

#include "../All2DEngine/GUI/UIScrollbar.h"	// Hinzugefügt von der Klassenansicht
#include "../All2DEngine/GUI/XMLDialogSystem.h"	// Hinzugefügt von der Klassenansicht
#include "../game/GameHighScore.h"
#include "../game/GameInstructions.h"
#include "../All2DEngine/All2D/All2D_Base/ImageText.h"
#include "../GAME/GameMessageBox.h"	// Added by ClassView
#include "HexxagonGame.h"	// Hinzugefügt von der Klassenansicht
#include "HexxagonMouseMover.h"	// Hinzugefügt von der Klassenansicht

class HexxagonGameController : public AppGameController
{
public:
	virtual bool paint(Image& backBuffer);
	virtual bool handleEvent(Event *evt);
	void init();
	HexxagonGameController();
	virtual ~HexxagonGameController();
//	friend vector<HexxagonStone*> HexxagonBoard::getStones();
	//friend class HexxagonBoard;

private:
	GameMessageBox myMsgBox;
	ImageText myFont;
	UIScrollBar myUI; 
	XMLDialogSystem myMenu;
	HexxagonGame hexGame;
	HexxagonMouseMover mouse;
	vector<ControllerAdapter*> vecCtrlAdapter;
	Image imgGFXElements;
	Image imgFrameBuffer;

	bool isExit;

protected:
	void setSettings();
};

#endif // !defined(AFX_BALLERGAMECONTROLLER_H__42480621_C0F3_11D5_B046_00E098802DF2__INCLUDED_)

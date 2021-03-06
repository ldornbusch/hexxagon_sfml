// HexxagonGameController.h: Schnittstelle f�r die Klasse HexxagonGameController.
// Handelt das Spiel als gesamtes:
// Start Bildschirm, Instruktions, HighScore usw
// Nicht zu verwechseln mit den ControllerAdaptern, die fuer die Uebersetzung der Steuerung notwendig sind
//////////////////////////////////////////////////////////////////////
#pragma once

#include <All2D/All2DEngine/All2D/All2D_Base/ImageText.h>
#include <All2D/All2DEngine/All2D/AppGameController.h>
#include <All2D/All2DEngine/Gui/UIScrollBar.h>
#include <All2D/All2DEngine/Gui/XMLDialogSystem.h>
#include "../Game/GameHighScore.h"
#include "../Game/GameInstructions.h"
#include "../Game/GameMessageBox.h"
#include "HexxagonGame.h"
#include "HexxagonMouseMover.h"

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

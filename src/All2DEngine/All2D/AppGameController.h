// GameControler.h: Schnittstelle für die Klasse GameControler.
// Der GameController regelt den Ablauf eines Spiels mit verschiedenen Teilen:
// z.B:
// Selection-Screen, HighScore, Instruction, Configs usw.
// Jedes Teil ist ein xContainer , der jeweils wieder in
// den GameController geAdded wird.

//////////////////////////////////////////////////////////////////////

#pragma once

#include "All2D_Controller.h"
#include "All2D_Events/MessageManager.h"
#include <string>
#include <vector>

using namespace std;

class AppGameController: public All2D_Controller
{
public:
	// consruct / deconstruct
	AppGameController();

  // container functions
	virtual bool  handleEvent(Event* evt);
	virtual bool  paint(Image& backBuffer);
private:
// eigentlich wollte ich nur die beiden Functionen paint und handleEvent des MessageManagers
// zu friends machen gab aber immer einen No NameSpace Error.. deswegen die ganze class als friend :-(
	friend class MessageManager;//::paint(Image& backBuffer);
protected:
	unsigned int iLoadReadyFlag;
	// manage game flow
	unsigned int		activeElement;
	unsigned int		newActiveElement;
	void	setActiveElement();

	virtual bool paintLoadScreen(Image& backBuffer);
	virtual bool paintRegularScreen(Image& backBuffer);
	bool blnLoadScreen;

	// load and save game data
	virtual void  loadGameData();
	virtual void  saveGameData();
};

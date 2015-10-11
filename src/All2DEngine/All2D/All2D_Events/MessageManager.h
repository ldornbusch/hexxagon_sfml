// MessageManager.h: Schnittstelle für die Klasse MessageManager.
// Enthält ein static drawable Element, das ein Container für alle anderen
// GUI Elements ist.. Windows Messages werden über den Manager verschickt
// und können durch seine static Functions auch von anderen Instanzen
// (z.B UIElement verschickt werden). Der Message Manager wird benutzt, um
// Die Einzelnen Komponenten miteinander kommunizieren zu lassen..
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
using namespace std;

#include "../AppGameController.h"
#include "../All2D_HAL/All2D_WinInterface.h"
#include "Event.h"

// pre-declaration
class AppGameController;

class MessageManager
{
public:
	static bool paint(CBitMap* backBuffer);		//This paint() makes Conversion CBitMap->Image
	static void setInterface(All2D_WinInterface* ptrWindow);
	static void processEvents();
	static bool paint(Image& backBuffer);
	static void setView(AppGameController* view);
	static bool handleEvent(Event* evt);
	MessageManager();
	virtual ~MessageManager();

private:
	static All2D_WinInterface* ptrWinInterface;
	static AppGameController* MainView;
	static vector<Event*>	vecEvents;
	static Image backBufferImage;	// This Image will only hold the BitMap structure for the All2D-Engine

protected:
};

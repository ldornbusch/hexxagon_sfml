// MessageManager.h: Schnittstelle f�r die Klasse MessageManager.
// Enth�lt ein static drawable Element, das ein Container f�r alle anderen
// GUI Elements ist.. Windows Messages werden �ber den Manager verschickt
// und k�nnen durch seine static Functions auch von anderen Instanzen
// (z.B UIElement verschickt werden). Der Message Manager wird benutzt, um
// Die Einzelnen Komponenten miteinander kommunizieren zu lassen..
//////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
using std::vector;

#include "../All2D_Controller.h"
#include "../All2D_HAL/All2D_WinInterface.h"
#include "Event.h"

// pre-declaration
class All2D_Controller;

class MessageManager
{
public:
	static bool paint(CBitMap* backBuffer);		//This paint() makes Conversion CBitMap->Image
	static void setInterface(All2D_WinInterface* ptrWindow);
	static void processEvents();
	static bool paint(Image& backBuffer);
	static void setView(All2D_Controller* view);
	static bool handleEvent(Event* evt);
	MessageManager();
	virtual ~MessageManager();

private:
	static All2D_WinInterface* ptrWinInterface;
	static All2D_Controller* MainView;
	static vector<Event*>	vecEvents;
	static Image backBufferImage;	// This Image will only hold the BitMap structure for the All2D-Engine

protected:
};

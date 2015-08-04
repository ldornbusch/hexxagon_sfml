// MessageManager.h: Schnittstelle für die Klasse MessageManager.
// Enthält ein static drawable Element, das ein Container für alle anderen 
// GUI Elements ist.. Windows Messages werden über den Manager verschickt 
// und können durch seine static Functions auch von anderen Instanzen
// (z.B UIElement verschickt werden). Der Message Manager wird benutzt, um
// Die Einzelnen Komponenten miteinander kommunizieren zu lassen..
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGEMANAGER_H__343FC215_75C0_44F6_8BDF_A64756173867__INCLUDED_)
#define AFX_MESSAGEMANAGER_H__343FC215_75C0_44F6_8BDF_A64756173867__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	static bool handleOSMessages(Event*evt);
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
	static bool keys[256];
	static Image backBufferImage;	// This Image will only hold the BitMap structure for the All2D-Engine

protected:
};

#endif // !defined(AFX_MESSAGEMANAGER_H__343FC215_75C0_44F6_8BDF_A64756173867__INCLUDED_)

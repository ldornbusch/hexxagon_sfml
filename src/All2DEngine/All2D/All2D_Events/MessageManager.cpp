// MessageManager.cpp: Implementierung der Klasse MessageManager.
//
//////////////////////////////////////////////////////////////////////

#include "MessageManager.h"
#include "../All2D_System.h"
All2D_WinInterface* MessageManager::ptrWinInterface = NULL;
AppGameController* MessageManager::MainView=NULL;
Image MessageManager::backBufferImage;
vector<Event*> MessageManager::vecEvents;
bool	MessageManager::keys[256];
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

MessageManager::MessageManager()
{
	for (int x=0;x<256;x++)
		keys[x]=false;
}

MessageManager::~MessageManager()
{
}

// this Message handles the Messages, which come from the OS-Windows System...
// This Messages will be recorded, and stored, for Help-System
bool MessageManager::handleOSMessages(Event *evt)
{
/* 	if (evt->Type==MM_KEYDOWN)
 * 		keys[(char)evt->wData]=true;
 * 	if (evt->Type==MM_KEYUP)
 * 		keys[(char)evt->wData]=false;
 */

	return handleEvent(evt);
}

// adds an Event into the stack
bool MessageManager::handleEvent(Event *evt)
{
	vecEvents.insert(vecEvents.end(), evt);
	return true;
}

void MessageManager::setView(AppGameController *view)
{
	MainView=view;
}

bool MessageManager::paint(Image& backBuffer)
{
	bool retVal=false;
	if (MainView!=NULL)
		retVal = MainView->masterPaint(backBuffer);
	return retVal;
}


// Diese Methode wird von masterPaint(..) aufgerufen
// und convertiert das CBitMap* in ein Image und ruft
// paint(Image& img) auf..
// DIESE ROUTINE WIRD NUR VON EINER INSTANZ benutzt...(Dem sog. View des All2D Windows)
bool MessageManager::paint(CBitMap *BackBuffer)
{
	bool isExit;
	if ( BackBuffer != NULL) {
		backBufferImage.setBitMap(BackBuffer);
		isExit=paint(backBufferImage);
		backBufferImage.setBitMap(NULL);	// sonst gibt es ein MemoryLeak, da das CBitmap* zweimal geloescht wird
	}

	return isExit;
}


//removes all Events from the stack
void MessageManager::processEvents()
{
	if (MainView!=NULL)
	{
		vector<Event*> myVec;
		for (vector<Event*>::iterator x=vecEvents.begin(); x!=vecEvents.end(); x++)
		{
			myVec.insert(myVec.end(),(*x));
		}

		vecEvents.clear();

		for (vector<Event*>::iterator x=myVec.begin(); x!=myVec.end(); x++)
			if ((*x)->Type==MM_SETFULLSCREEN)
			{	// Here are the All2D-WindowCommands implemented.. 2Do: make it nicer
				if (ptrWinInterface){
					ptrWinInterface->setFullscreen((bool)(*x)->wData);
				}

			}else
				MainView->handleEvent((*x));

		for (vector<Event*>::iterator x=myVec.begin(); x!=myVec.end(); x++)
			delete (*x);

		myVec.clear();
	}
}
void MessageManager::setInterface(All2D_WinInterface* view){
    MessageManager::ptrWinInterface = view;
}

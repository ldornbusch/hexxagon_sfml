// GameController.cpp: Implementierung der Klasse GameControler.
//
//////////////////////////////////////////////////////////////////////

#include "AppGameController.h"
#include "All2D_Events/MessageManager.h"
#include "All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

AppGameController::AppGameController() : All2D_Controller("GameController")
{
	activeElement=0;
	newActiveElement=0;
	blnLoadScreen=false;
	iLoadReadyFlag=0;
}

void AppGameController::setActiveElement()
{
	xElement* x = modules[activeElement];
	if (x)
		(x)->finish();

	activeElement=newActiveElement;

	x = modules[activeElement];
	if (x){
		(x)->init();
		blnLoadScreen=true;
	}
}

bool AppGameController::handleEvent(Event *evt)
{
	if (activeElement>=0 && activeElement<modules.size())
		return xContainer::modules[activeElement]->handleEvent(evt);
	else
		return false;
}


bool AppGameController::paint(Image& backBuffer)
{
	if (blnLoadScreen)
		paintLoadScreen(backBuffer);
	else
		paintRegularScreen(backBuffer);

	return true;
}
// This Method paints the regular Gamescreen it is always called
// except if the blnLoadScreen flag is set then the paintLoadScreen(..) is called
bool AppGameController::paintRegularScreen(Image& backBuffer)
{
	if (activeElement>=0 && activeElement<modules.size())
		return xContainer::modules[activeElement]->paint(backBuffer);
	else
		return false;
}

// This method is called when the the application is loading some Pictures
// The Paint Method of te childs will not be called except the PaintLogo
// which will be placed on top of Screen. The GameScreen will be painted once,
// to erase the MousePointer..
bool AppGameController::paintLoadScreen(Image& backBuffer)
{
	return true;
}

void AppGameController::saveGameData()
{
}

void AppGameController::loadGameData()
{
}

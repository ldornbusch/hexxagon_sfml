// All2D_System.cpp: Implementierung der Klasse All2D_System.
//
//////////////////////////////////////////////////////////////////////

#include "All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

//xRegistry All2D_System::Registry("SOFTWARE\\hexerei software creations\\games\\columns");

bool	All2D_System::fullScreen = false;
float All2D_System::skipFactor=1.0f;	// keine AnimationsFrames skippen

int All2D_System::fixedBits = 0;
int All2D_System::fixedX = 0;
int All2D_System::fixedY = 0;

sf::Clock  All2D_System::Timer =sf::Clock();

string All2D_System::WinTitle	=	"";
string All2D_System::loadPath	=	"";

Image All2D_System::UIElements;
ImageText All2D_System::SystemFont;

//HWND All2D_System::hWnd=0;

SpriteManager All2D_System::spriteManager=SpriteManager();
SoundEngine* All2D_System::sound = SoundFactory::getInstance(3);

//CDebug All2D_System::Debug;


// returns MouseCoords from backed event variables
Point All2D_System::extractMouseCoords(Event *evt)
{
	Point retVal;
	retVal.x=evt->lData & 0x0000ffff;
	retVal.y=(evt->lData & 0xffff0000)>>16;
	return retVal;
}
unsigned int All2D_System::getTime()
{
	return All2D_System::Timer.getElapsedTime().asMilliseconds();//TODO: replace timeGetTime();
}

// return the full path to the image file depending on the current resolution
string All2D_System::dataPath(string szFile) {
	return szFile;
}

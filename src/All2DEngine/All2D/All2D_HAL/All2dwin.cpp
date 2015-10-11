// All2DWin.cpp: Implementierung der Klasse All2DWin.
//
//////////////////////////////////////////////////////////////////////
//#include <ddraw.h>
#include "All2DWin.h"
#include "../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
All2DWin::All2DWin()//, bool Fullscr ,int winWidth, int winHeight)
{
	WindowX = All2D_System::fixedX;		// Window is WindowX px wide
	WindowY = All2D_System::fixedY;		// Window is WindowY px large
	bFullScreen=All2D_System::fullScreen;
	bDebugWinLook = !bFullScreen; // we will have a frame and such things...
	strTitle=All2D_System::WinTitle;
	DisplayDepht = WINPLANES;	// We want to have WINPLANES Bits per Pixel
	bReady=false;
	bSmooth=false;
	InitWindow();	// Make the Window
	MessageManager::setInterface(this);
}


void All2DWin::init()
{
}


// This Routine sets the View which controls the program
int All2DWin::startApp(AppGameController& dE)
{
	MessageManager::setView(&dE);
	return MessageLoop();
}


void All2DWin::setFullscreen(bool blnFlag)
{
	if (bFullScreen!=blnFlag) {
		ChangeCoopLevel();
	}
}
void All2DWin::setSmooth(bool blnSmooth)
{
    bSmooth = blnSmooth;
}

void All2DWin::All2D_Exit()
{
	sfml_window.close();
}


// private Method to initialize the Window...
void All2DWin::InitWindow()
{
    sfml_window.create(sf::VideoMode(WindowX,WindowY),strTitle,bFullScreen?sf::Style::Fullscreen : sf::Style::Default);
    sfml_window.setFramerateLimit(60);
}

// This Method changes between Fullscreen and windowed mode..
void All2DWin::ChangeCoopLevel()
{
    bFullScreen=!bFullScreen;
    sfml_window.close();
    InitWindow();
}

Rect All2DWin::getWindowPosition()
{
    Rect retVal;
    retVal.x1 = sfml_window.getPosition().x;
    retVal.y1 = sfml_window.getPosition().y;
    retVal.x2 = sfml_window.getSize().x;
    retVal.y2 = sfml_window.getSize().y;
    return retVal;
}

// returns MouseCoords transformed to 0-winX/0-winY
void All2DWin::transformMouseCoords(Event *evt)
{
	//Point retVal;
	double x=(double)(evt->lData & 0x0000ffff);
    x= x / sfml_window.getSize().x * All2D_System::fixedX;

	double y=((double)((evt->lData & 0xffff0000)>>16));
    y = y /sfml_window.getSize().y * All2D_System::fixedY;

    evt->lData=((int)y)<<16 | ((int)x);
}


// This is the Mainloop, where the Program (View) runs...
int All2DWin::MessageLoop()	//drawableElement.UpdateFrame () wird von Hier aufgerufen
{
    sf::Texture txt;

    CBitMap* surface=new CBitMap(640,480);
    surface->Clear(0);
    sf::Image img;
    surface->returnImage(img);
    txt.loadFromImage(img);
    sf::Sprite sp(txt);
    sp.setPosition(0,0);
    sp.setScale(1.0f,1.0f);

    while (sfml_window.isOpen()){
        sf::Event event;
        while (sfml_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                sfml_window.close();
            }

            Event* HAL_Event = new Event(0,0,0);
            if(event.type == sf::Event::MouseMoved){
                HAL_Event->Type=MM_MOUSEMOVE;
                HAL_Event->lData = event.mouseMove.y << 16 | event.mouseMove.x;
                transformMouseCoords(HAL_Event);
            }
            if(event.type == sf::Event::MouseButtonPressed){
                HAL_Event->Type=MM_LBUTTONDOWN;
                HAL_Event->lData = event.mouseButton.y << 16 | event.mouseButton.x;
                transformMouseCoords(HAL_Event);
            }
            if(event.type == sf::Event::MouseButtonReleased){
                HAL_Event->Type=MM_LBUTTONUP;
                HAL_Event->lData = event.mouseButton.y << 16 | event.mouseButton.x;
                transformMouseCoords(HAL_Event);
            }

            if(event.type == sf::Event::KeyPressed){
                HAL_Event->Type=MM_KEYDOWN;
                HAL_Event->wData=event.key.code;
            }
            if(event.type == sf::Event::KeyReleased){
                HAL_Event->Type=MM_KEYUP;
                HAL_Event->wData=event.key.code;
            }

            MessageManager::handleEvent(HAL_Event);
        }
        MessageManager::processEvents();
        bool isExit=MessageManager::paint(surface);
        if (!isExit){
            All2D_Exit();
        }
        surface->returnImage(img);
        txt.loadFromImage(img);
        txt.setSmooth(bSmooth);
        sfml_window.clear();
        sfml_window.draw(sp);//,sf::BlendAdd);
        sfml_window.display();
    }
    return 0;
}



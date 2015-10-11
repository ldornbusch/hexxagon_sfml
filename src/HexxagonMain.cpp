//#define INITGUID

#include "hexxagon/HexxagonGameController.h"
#include "All2DEngine/All2D/All2D_System.h"
#include "All2DEngine/All2D/All2D_HAL/All2DWin.h"

LRESULT CALLBACK MainWndProc (HWND ,UINT,WPARAM ,LPARAM);
All2D_WinInterface *myWin=NULL;					// Die Window-Klasse für DirectDraw Window
//
// initialize static system object
// ------------------------------------------------------
// get and set registry defaults if not present
//
bool initAll2D()
{
	All2D_System::fixedBits=16;
	All2D_System::fixedX=640;
	All2D_System::fixedY=480;
	All2D_System::fullScreen=false;
	All2D_System::WinTitle="Hexxagon by Hexerei, (c) 2002";
	All2D_System::setRenderMode(ALL2D);

	All2D_System::UIElements.loadImage("data/All2D_UI.png");
	All2D_System::SystemFont.cloneImage(All2D_System::UIElements,Rect(0,32,320,128));
	All2D_System::SystemFont.FontInit(16,16,10,"0123456789.,+-*/!?$&()§ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz:[]");
    myWin = new All2DWin();
	myWin->init();

	PicLoader::init();
	return true;
}

int main()
{
	int a=0;

	initAll2D();

	// constructor calls request loads
	HexxagonGameController Hexxagon;


	/*
	 * load all buffered images and post progress
	 */
	int c=0;

	while (c>=0)
	{
		c=PicLoader::loadAllBitMaps();
	}

	/*
	 * init window and game controller and start main loop
	 */
	Hexxagon.init();

	a=myWin->startApp(Hexxagon);		// Dies ist die Hauptschleife..

	Hexxagon.finish();			// drawableElement aufräumen

	delete myWin;
	return a;
}


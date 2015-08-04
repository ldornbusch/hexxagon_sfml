//#define INITGUID

#include <windows.h>
#include "hexxagon/HexxagonGameController.h"
#include "All2DEngine/All2D/All2D_System.h"
#include "All2DEngine/All2D/All2D_HAL/All2DWin.h"
//#include "All2DEngine/All2D/All2D_HAL/GLWindow.h"
#include <time.h>

LRESULT CALLBACK MainWndProc (HWND ,UINT,WPARAM ,LPARAM);
All2D_WinInterface *myWin=NULL;					// Die Window-Klasse für DirectDraw Window
//
// initialize static system object
// ------------------------------------------------------
// get and set registry defaults if not present
//
//bool initAll2D(HINSTANCE   hInstance,HINSTANCE   hPrevInstance)
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
//	myWin = new All2DWin( hInstance, hPrevInstance, MainWndProc);
//	myWin = new GLWindow( hInstance, hPrevInstance, MainWndProc);
	myWin->init();

	PicLoader::init();
	return true;
}

/*int PASCAL
WinMain(HINSTANCE   hInstance,
        HINSTANCE   hPrevInstance,
        LPSTR       lpszCmdLine,
        int         nCmdShow)
*/
int main()
{
	int a=0;

//	initAll2D(hInstance, hPrevInstance);
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


//-----------------------------------------------------------------------------
// Name: MainWndProc()
// Desc: The Main Window Procedure - Habe ich leider nicht in die Klasse packen können...(CallBack function)
/*LRESULT CALLBACK
MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (myWin)	//Bei der Initialisierung wird die Routine schon aufgerufen ohne gültiges Object..
	{
		myWin->WndProc(hWnd, msg, wParam, lParam);
		if (All2D_System::sound)
			All2D_System::sound->updateStatus();
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
*/
//-----------------------------------------------------------------------------


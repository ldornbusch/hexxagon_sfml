// All2DWin.h: Schnittstelle für die Klasse All2DWin.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <SFML/Graphics.hpp>

#include <string>
using namespace std;

#include "Bitmap.h"
#include "All2D_WinInterface.h"
#include "../All2D_Events/MessageManager.h"


#define WINX	640
#define WINY	480
// #define WINPLANES 32			// WIRD NUN IN BitMap.h definiert...Ldornbusch 15.04.2001

class All2DWin : public All2D_WinInterface
{
public:
	void All2D_Exit();
	void setFullscreen(bool blnFlag);
	void setSmooth(bool blnSmooth);
	Rect getWindowPosition();
    void transformMouseCoords(Event *evt);
	void init();
	int startApp(All2D_Controller& dE);

    All2DWin();
private:
	int MessageLoop();
	void InitWindow();
	void ChangeCoopLevel();

	int BitsPixel;
	int WindowX;
	int WindowY;
	int DisplayDepht;
	bool bSmooth;
	bool bReady;
	bool bActive;
	string strTitle;
    sf::RenderWindow sfml_window;
};

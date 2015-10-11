// All2DWin.h: Schnittstelle f�r die Klasse All2DWin.
//
//////////////////////////////////////////////////////////////////////
#define INITGUID

#if !defined(AFX_All2DWin_H__07C97742_8027_11D3_A6F8_0080AD40DBC7__INCLUDED_)
#define AFX_All2DWin_H__07C97742_8027_11D3_A6F8_0080AD40DBC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	void init();
	int startApp(AppGameController& dE);

    All2DWin();
private:
	bool bDebugWinLook;
	int MessageLoop();
	void InitWindow();
	void ChangeCoopLevel();

	int BitsPixel;
	int WindowX;
	int WindowY;
	int DisplayDepht;
	bool bFullScreen;
	bool bReady;
	bool bActive;
	string strTitle;
    sf::RenderWindow sfml_window;
};

#endif // !defined(AFX_All2DWin_H__07C97742_8027_11D3_A6F8_0080AD40DBC7__INCLUDED_)

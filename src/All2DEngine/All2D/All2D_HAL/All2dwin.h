// All2DWin.h: Schnittstelle für die Klasse All2DWin.
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

//#define HERMES_INITFAIL 10
//#define HERMES_DONEFAIL 11
//#define HERMESBUFFER_FAILED 12
//#define HERMES_CONV_NOTFOUNT 13
//#define HERMES_NO_DXPIXFORM 14

class All2DWin : public All2D_WinInterface
{
public:
	void All2D_Exit();
	void setFullscreen(bool blnFlag);
	void init();
	int startApp(AppGameController& dE);
//	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    All2DWin();
	//All2DWin(HINSTANCE hInstance, HINSTANCE hPrevInstance, WNDPROC MainWndProc);//, bool Fullscr=true, int winWidth=WINX, int winHeight=WINY);
private:
	bool bDebugWinLook;
	int MessageLoop();
//	void InitWindow(WNDPROC MainProc);
	void InitWindow();
	void ChangeCoopLevel();

	int BitsPixel;
	int WindowX;
	int WindowY;
	int DisplayDepht;
	bool bFullScreen;
	bool bReady;
	bool bActive;
	bool bHermes;
	string strTitle;
    sf::RenderWindow sfml_window;
//	HINSTANCE hInstance;
//	HINSTANCE hPrevInstance;
//	HWND hWnd;
//	HACCEL hAccel;
//	RECT rcWindow;
//	RECT rcScreen;
//	RECT rcViewPort;
//	CBitMap* HermesBuffer;							// Hermes-Buffer (if no 640x480x32 is available)
//	HermesHandle HermesConverter;
//	HermesFormat* DirectXBufferFormat;
//	HermesFormat* HermesBufferFormat;
//	DDSURFACEDESC sdesc;
//	LPDIRECTDRAWSURFACE BackBuffer;			// DirectX-Backbuffer
//	LPDIRECTDRAWSURFACE Primary;			// DirectX-Frontbuffer
//	LPDIRECTDRAW2 dd;						// Direct Draw Object
};

#endif // !defined(AFX_All2DWin_H__07C97742_8027_11D3_A6F8_0080AD40DBC7__INCLUDED_)

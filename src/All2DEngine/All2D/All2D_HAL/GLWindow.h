// GLWindow.h: Schnittstelle für die Klasse CGLWindow.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLWINDOW_H__E323E2E3_4043_11D4_B941_0000E8699C86__INCLUDED_)
#define AFX_GLWINDOW_H__E323E2E3_4043_11D4_B941_0000E8699C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <winuser.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>

#include "All2D_WinInterface.h"
#include "BitMap.h"

class GLWindow  : public All2D_WinInterface
{
private:
	static void InterpretError(DWORD wert);
	HDC		hDC	;		// Handle Device Context
	HGLRC	hRC	;		// Handle Rendering Context
	HWND	hWnd;		// Handle Window
	static LRESULT CALLBACK DialogProc (HWND, UINT, WPARAM, LPARAM);
	static POINT MousePos;
	int MessageLoop();
	CBitMap* All2D_Screen;
	GLuint All2D_GLTextureID;
public:
	void All2D_Exit();
	void setFullscreen(bool blnFlag);
	void init();
	int startApp(AppGameController& dE);
	LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static float speed;
	char* LoadDlg();
	void SetWindowTitle(char* Title);
	HDC GetDeviceContext();
	HWND GetWindowHandle();
	int GetMouseX();
	int GetMouseY();
	POINT GetMousePos();
	static bool RightMouseButton;
	static bool LeftMouseButton;
	static bool	*keys;
	static bool	active			;
	bool	fullscreen	;

	static GLvoid	ReSizeGLScene(GLsizei width, GLsizei height);
	int InitGL (GLvoid);
	int ClearGLScene(GLvoid);
	GLvoid	KillGLWindow(GLvoid);
	HWND	CreateGLWindow(const char* title="Default Title", int width=640, int height=480, int bits=32, bool full=false, WNDPROC MainWndProc=NULL);
	HDC		GetGLDC()	;		// Handle Device Context
	GLWindow(HINSTANCE hInst, HINSTANCE hPrevInst, WNDPROC MainWndProc); //, bool Fullscr ,int winWidth, int winHeight);
	virtual ~GLWindow();

};


#endif // !defined(AFX_GLWINDOW_H__E323E2E3_4043_11D4_B941_0000E8699C86__INCLUDED_)

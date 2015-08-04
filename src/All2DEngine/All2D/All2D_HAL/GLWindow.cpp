// GLWindow.cpp: Implementierung der Klasse GLWindow.
//
//////////////////////////////////////////////////////////////////////

#define _WIN32_WINDOWS 0x0500

#pragma comment( lib, "opengl32.lib" )
#pragma comment( lib, "glu32.lib" )

#include "GLWindow.h"
#include "../includes/resource.h"
#include "../AppGameController.h"
#include "../All2D_System.h"


	bool	*GLWindow::keys=new bool[256];
	POINT	GLWindow::MousePos;
	bool	GLWindow::LeftMouseButton=false;
	bool	GLWindow::RightMouseButton=false;
	bool	GLWindow::active=false;
	float GLWindow::speed=6.1f;

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

GLWindow::GLWindow(HINSTANCE hInst, HINSTANCE hPrevInst, WNDPROC MainWndProc)//, bool Fullscr ,int winWidth, int winHeight)
{
	for (int x=0; x<256; x++) GLWindow::keys[x]=false;
	hDC	= NULL;		// Handle Device Context
	hRC	=	NULL;		// Handle Rendering Context
	hWnd=	NULL;		// Handle Window
	fullscreen=true;
	active=false;

	All2D_Screen=new CBitMap(1024,512);	// OpnGLCompatible  texturformat

	All2D_System::hWnd = CreateGLWindow(All2D_System::WinTitle.c_str(),All2D_System::fixedX,All2D_System::fixedY, All2D_System::fixedBits, All2D_System::fullScreen, MainWndProc);	// Make the Window
	MessageManager::setInterface(this);

}

GLWindow::~GLWindow()
{
	hDC	= NULL;		// Handle Device Context
	hRC	=	NULL;		// Handle Rendering Context
	hWnd=	NULL;		// Handle Window
}

int GLWindow::GetMouseX()
{
	if (MousePos.x==0)
		GetMousePos();
	int back=MousePos.x;
	MousePos.x=0;
	return back;	
}
int GLWindow::GetMouseY()
{
	if (MousePos.y==0)
		GetMousePos();
	int back=MousePos.y;
	MousePos.y=0;
	return back;	
}
POINT GLWindow::GetMousePos()
{
	if (active) 
	{
		GetCursorPos(&MousePos);
		SetCursorPos(320,240);
	}
	return MousePos;	
}

GLvoid	GLWindow::ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height==0)	height=1;

	//glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluPerspective(45.0f, (GLfloat) width/(GLfloat) height,1.0f,5000.0f);
	//gluPerspective(45.0f, (GLfloat) width/(GLfloat) height,1.0f,5000.0f);
	glViewport(0,0,640,480);
	//glFrustum(-320,320,-240,240,4.0,1000.0);
	//gluOrtho2D(0,640,0,480);
	glOrtho(0.0,640.0,480.0,0.0,-100.0,100.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

int GLWindow::InitGL (GLvoid)
{
	// OpenGL--ScreenSurfaceTexture erstellen..
	glGenTextures(1,&All2D_GLTextureID);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing

	return TRUE;
}

int GLWindow::ClearGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	return true;
}

GLvoid	GLWindow::KillGLWindow(GLvoid)
{
	if (hRC)
	{
		if (!wglMakeCurrent(NULL,NULL))	MessageBox(NULL,"Release of DC and RC failed.","SHUTDOWN ERROR",MB_OK|MB_ICONINFORMATION);
		if (!wglDeleteContext(hRC))			MessageBox(NULL,"Release Rendering Context failed.", "SHUTDOWN ERROR", MB_OK|MB_ICONINFORMATION);
		hRC=NULL;
	}
	if (hDC && !ReleaseDC(hWnd, hDC))
	{
		MessageBox(NULL, "Release Device Context failed.","SHUTDOWN ERROR", MB_OK|MB_ICONINFORMATION);
		hDC=NULL;
	}
	if (hWnd && !DestroyWindow(hWnd))
	{
		MessageBox(NULL, "Could not release hWnd.","SHUTDOWN ERROR", MB_OK|MB_ICONINFORMATION);
		hWnd=NULL;
	}
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}
}

HWND GLWindow::GetWindowHandle()
{
	return hWnd;
}

HDC GLWindow::GetDeviceContext()
{
	return hDC;
}

void GLWindow::SetWindowTitle(char *Title)
{
	SetWindowText(hWnd, Title);
}

HDC GLWindow::GetGLDC(){ return hDC;}

HWND GLWindow::CreateGLWindow(const char* title, int width, int height, int bits, bool full, WNDPROC MainWndProc)
{
	bool fullscreen=full;
	GLuint			PixelFormat, xStart,yStart;
	HINSTANCE		hInstance;
	WNDCLASS		wc;
	DWORD			dwExStyle;
	DWORD			dwStyle;
	hInstance		= GetModuleHandle(NULL);		// Grab An Instance For Our Window
	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window
	wc.lpfnWndProc		= (WNDPROC) MainWndProc;			// WndProc Handles Messages
	wc.cbClsExtra		= 0;					// No Extra Window Data
	wc.cbWndExtra		= 0;					// No Extra Window Data
	wc.hInstance		= hInstance;				// Set The Instance
    wc.hIcon = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON));
//	wc.hIconSm= LoadIcon( hInstance, MAKEINTRESOURCE(IDI_MAIN_ICON)); 
    wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1) );
	wc.hbrBackground	= CreateSolidBrush(COLOR_BACKGROUND);					// No Background Required For GL
	wc.lpszMenuName		= 0;//MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName	= "OpenGL";				// Set The Class Name

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Failed to Register the WindowClass","SHUTDOWN ERROR", MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight= height;
		dmScreenSettings.dmBitsPerPel= bits;
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) !=DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "The Requested FullScreenMode is not supported by\nYour VideoCard. Use windowed Mode instead?","eclipse GLwin", MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;
			}
			else 
			{
				MessageBox(NULL, "Program will now close.","ERROR", MB_OK|MB_ICONSTOP);
				return false;
			}
		}
	}
	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle		= WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		ShowCursor(FALSE);
		xStart=0;yStart=0;
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle		= WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
		xStart=64;yStart=64;
	}
	int cx = width+GetSystemMetrics(SM_CXSIZEFRAME)*(fullscreen ? 0:2);
	int cy = height+GetSystemMetrics(SM_CYSIZEFRAME)*(fullscreen ? 0:2) + GetSystemMetrics(SM_CYCAPTION) * (fullscreen ? 0:1);

	if (!(hWnd=CreateWindowEx(	dwExStyle,
								"OpenGL",
								title,
								dwStyle,
								xStart,yStart, cx, cy,
								NULL,
								NULL,
								hInstance,
								NULL)))
	{
		KillGLWindow();
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	static PIXELFORMATDESCRIPTOR	pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | 
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER |
		PFD_TYPE_RGBA,
		bits,
		0, 0, 0, 0, 0, 0, 
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	if (!(hDC=GetDC(hWnd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't create A GL DeviceContext.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Find a suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't set the PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	if (!(hRC=wglCreateContext(hDC)))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	if (!wglMakeCurrent(hDC, hRC))
	{
		KillGLWindow();
		MessageBox(NULL,"Can't activate the GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ReSizeGLScene(width, height);
	if (!InitGL())
	{
		KillGLWindow();
		MessageBox(NULL,"Can't initialize GL Scene.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	SetCursorPos(320,240);
	return hWnd;
}

LRESULT GLWindow::WndProc(HWND	hWnd,			// Handle For This Window
				UINT	uMsg,			// Message For This Window
				WPARAM	wParam,			// Additional Message Information
				LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)
	{
		case WM_ACTIVATE:				// Watch For Window Activate Message		
		{
			if (LOWORD(wParam)==WA_INACTIVE || HIWORD(wParam)!=0)			// Check Minimization State			
			{
				active=false;			// Program Is Active	
//				SetCursor(LoadCursor(NULL, IDC_ARROW));
			}
			else			
			{
				active=true;			// Program Is No Longer Active			
			}
			
			return 0;				// Return To The Message Loop		
		}
		case WM_SYSCOMMAND:				// Intercept System Commands		
		{
				switch (wParam)				// Check System Calls			
				{
					case SC_SCREENSAVE:		// Screensaver Trying To Start?
					case SC_MONITORPOWER:		// Monitor Trying To Enter Powersave?
					return 0;			// Prevent From Happening			
				}			
				break;					// Exit		
		}
		case WM_CLOSE:					// Did We Receive A Close Message?		
		{
			PostQuitMessage(0);			// Send A Quit Message			
			break;						// Jump Back		
		}
		case WM_MOUSEMOVE:				// Is A Key Being Held Down?		
		{
			LeftMouseButton = ((wParam & MK_LBUTTON)!=0);              // key flags 
			if (LeftMouseButton)
				LeftMouseButton=true;
			RightMouseButton = ((wParam & MK_RBUTTON)!=0);              // key flags 
			if (RightMouseButton)
				RightMouseButton=true;
			break;;				// Jump Back
		}
		case WM_RBUTTONDOWN:
		{
			RightMouseButton = true;			// If So, Mark It As TRUE		
			break;				// Jump Back
		}
		case WM_RBUTTONUP:	
		{
			RightMouseButton = false;			// If So, Mark It As TRUE		
			break;				// Jump Back
		}
		case WM_LBUTTONDOWN:
		{
			LeftMouseButton = true;			// If So, Mark It As TRUE		
			break;				// Jump Back
		}
		case WM_LBUTTONUP:	
		{
			LeftMouseButton = false;			// If So, Mark It As TRUE		
			break;				// Jump Back
		}
		case WM_MOUSEWHEEL:
		{

			speed += (short) HIWORD(wParam) / 60;   
			if (speed<0)
				speed=0;
			break;
		}
		case WM_KEYDOWN:				// Is A Key Being Held Down?		
		{
			keys[wParam] = TRUE;			// If So, Mark It As TRUE		
			break;				// Jump Back
		}
		case WM_KEYUP:					// Has A Key Been Released?		
		{
			keys[wParam] = FALSE;			// If So, Mark It As FALSE
			break;				// Jump Back		
		}
		case WM_SIZE:					// Resize The OpenGL Window		
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;				// Jump Back		
		}	
		case WM_COMMAND:
		{
		}

		
	}

	Event* myEvent=new Event(uMsg,wParam, lParam);
	MessageManager::handleOSMessages(myEvent);
	return (LRESULT)0;
	//return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK GLWindow::DialogProc(HWND	hWnd,			// Handle For This Window
				UINT	uMsg,			// Message For This Window
				WPARAM	wParam,			// Additional Message Information
				LPARAM	lParam)			// Additional Message Information
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            return TRUE;
        case WM_COMMAND:
            switch (wParam)
            {
				case IDCANCEL:
				case IDOK:
                    EndDialog(hWnd, TRUE);
                    return TRUE;
				default:
				break;
            }
            break;
    }
	return 0L;
}

void GLWindow::All2D_Exit()
{
	PostMessage(hWnd, WM_CLOSE, 0, 0);
}

void GLWindow::init()
{
}

void GLWindow::setFullscreen(bool blnFlag)
{
//	if (bFullScreen!=blnFlag) {
//		ChangeCoopLevel();
//	}
}

// This Routine sets the View which controls the program
int GLWindow::startApp(AppGameController& dE)
{
	MessageManager::setView(&dE);
	return MessageLoop();
}

// This is the Mainloop, where the Program (View) runs...
int GLWindow::MessageLoop()	//drawableElement.UpdateFrame () wird von Hier aufgerufen
{
	MSG		msg;
	static bool isExit=true;
	int newtime, lasttime;
	while (TRUE)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)
				break;
			else 
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else
//			if (bActive && bReady)
			{ //                    Idle processing
				lasttime =GetTickCount();

				
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				MessageManager::processEvents();
				isExit=MessageManager::paint(All2D_Screen); 	//Creates a CBitmap of the Backbuffer, or the HermesBuffer

				glLoadIdentity();									// Reset The View
				
				
/**/
				//static float rot=180.0f;
				//rot=180.0f;
				//glRotatef(rot,0.0f,0.0f,1.0f);
				glTranslatef(0.0f,0.0f,-100.0f);
				//glTranslatef(0.0f,0.0f,-4.1f);
				//glTranslatef(0.0f,0.15f,-6.5f);
				//glTranslatef(0.0f,0.15f,-8.0f);

				glBindTexture(GL_TEXTURE_2D, All2D_GLTextureID);

				glTexImage2D(GL_TEXTURE_2D, 0, 4, 1024, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, All2D_Screen->getBitmap());
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);// Linear Filtering
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);// Linear Filtering

				glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )

				glBegin(GL_QUADS);
 					glColor3f(1.0f,1.0f,1.0f);

					glTexCoord2f(0.625f,0.9375f);
					glVertex3f(640.0f,480.0f,0.0f);

					glTexCoord2f(0.625f,0.0f);
					glVertex3f(640.0f, 0.0f,0.0f);

					glTexCoord2f(0.0f,0.0f);
					glVertex3f( 0.0f, 0.0f,0.0f);

					glTexCoord2f(0.0f,0.9375f);
					glVertex3f( 0.0f,480.0f,0.0f);

				glEnd();

				SwapBuffers(hDC);
/**/
//				isExit=MessageManager::paint(MakeBitMap()); 	//Creates a CBitmap of the Backbuffer, or the HermesBuffer
//				CopyHermesToBackBuffer();										//Actualize the BackBuffer (if needed)
//				Flip();

//				if (!bFullScreen)
				{
					newtime =GetTickCount();
					float FPS;
					char	dummy[60];
					string newDummy;
					if (newtime==lasttime) {
						wsprintf(dummy,"Too fast for me!!;-)");
					}else{
						newtime=newtime-lasttime;
						FPS=(float)1000/(newtime);
						wsprintf(dummy,"Max Time: %d FpS" ,(int)(FPS));
						newDummy=dummy;
					}

					SetWindowText(hWnd, newDummy.c_str());
				}
				if (!isExit)
					PostMessage(hWnd, WM_CLOSE, 0, 0);
			}
//			else
		//	{   WaitMessage();   }
		}
	return msg.wParam;
}

void GLWindow::InterpretError(DWORD wert)
{
	char* ErrorMsg="Keine Message gefunden!";
	switch (wert)
	{
		case CDERR_FINDRESFAILURE:
			ErrorMsg="CDERR_FINDRESFAILURE";
			break;
		case CDERR_INITIALIZATION:
			ErrorMsg="CDERR_INITIALIZATION";
			break;
		case CDERR_LOCKRESFAILURE:
			ErrorMsg="CDERR_LOCKRESFAILURE";
			break;
		case CDERR_LOADRESFAILURE:
			ErrorMsg="CDERR_LOADRESFAILURE";
			break;
		case CDERR_LOADSTRFAILURE:
			ErrorMsg="CDERR_LOADSTRFAILURE";
			break;
		case CDERR_MEMALLOCFAILURE:
			ErrorMsg="CDERR_MEMALLOCFAILURE";
			break;
		case CDERR_MEMLOCKFAILURE:
			ErrorMsg="CDERR_MEMLOCKFAILURE";
			break;
		case CDERR_NOHINSTANCE:
			ErrorMsg="CDERR_NOHINSTANCE";
			break;
		case CDERR_NOHOOK:
			ErrorMsg="CDERR_NOHOOK";
			break;
		case CDERR_NOTEMPLATE:
			ErrorMsg="CDERR_NOTEMPLATE";
			break;
		case CDERR_STRUCTSIZE:
			ErrorMsg="CDERR_STRUCTSIZE";
			break;
		case FNERR_BUFFERTOOSMALL:
			ErrorMsg="FNERR_BUFFERTOOSMALL";
			break;
		case FNERR_INVALIDFILENAME:
			ErrorMsg="FNERR_INVALIDFILENAME";
			break;
		case FNERR_SUBCLASSFAILURE:
			ErrorMsg="FNERR_SUBCLASSFAILURE";
			break;
		default:
			break;
	}
	MessageBox(NULL,ErrorMsg, "All3D ErrorMsg", MB_OK);
}

char* GLWindow::LoadDlg()
{
	HRESULT res;
	int a;

	OPENFILENAME ofn;       // common dialog box structure
	static char* szFile =NULL;
	if (szFile) {
		delete [] szFile;
		szFile=NULL;
	}
	szFile = new char[260];       // buffer for filename
	for (a=0; a<260; a++)
		szFile[a]=0;

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = 260;
	ofn.lpstrFilter = "All\0*.*\0Cyberia Worlds\0*.3ds";
	ofn.nFilterIndex = 2;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 
	res=GetOpenFileName(&ofn);
	if (res!=TRUE) 
		return "";
	// Get only the FileName without the Path...
	return ofn.lpstrFile+ofn.nFileOffset;
}

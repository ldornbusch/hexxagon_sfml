// All2DWin.cpp: Implementierung der Klasse All2DWin.
//
//////////////////////////////////////////////////////////////////////
//#include <ddraw.h>
#include "All2DWin.h"
#include "../All2D_System.h"




// -------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

/*All2DWin::All2DWin(HINSTANCE hInst, HINSTANCE hPrevInst, WNDPROC MainWndProc)//, bool Fullscr ,int winWidth, int winHeight)
{

	bHermes=false;		// We do not use Hermes at the moment..
	WindowX = All2D_System::fixedX;		// Window is WindowX px wide
	WindowY = All2D_System::fixedY;		// Window is WindowY px large
	bFullScreen=All2D_System::fullScreen;
	bDebugWinLook = !bFullScreen; // we will have a frame and such things...
	strTitle=All2D_System::WinTitle;
	DisplayDepht = WINPLANES;	// We want to have WINPLANES Bits per Pixel
//	HermesBuffer=NULL;	// We do not have a HermesBuffer
//	BackBuffer=NULL;	// No BackBuffer
//	Primary=NULL;		// No PrimaryBuffer (which is alltimes visible)
//	dd=NULL;			// No DirectDrawObject
//	hInstance=hInst;		// The Windows Instance
//	hPrevInstance=hPrevInst;
	bReady=false;
//	All2D_System::hWnd = InitWindow(MainWndProc);	// Make the Window
	MessageManager::setInterface(this);
}
*/
All2DWin::All2DWin()//, bool Fullscr ,int winWidth, int winHeight)
{

	bHermes=false;		// We do not use Hermes at the moment..
	WindowX = All2D_System::fixedX;		// Window is WindowX px wide
	WindowY = All2D_System::fixedY;		// Window is WindowY px large
	bFullScreen=All2D_System::fullScreen;
	bDebugWinLook = !bFullScreen; // we will have a frame and such things...
	strTitle=All2D_System::WinTitle;
	DisplayDepht = WINPLANES;	// We want to have WINPLANES Bits per Pixel
//	HermesBuffer=NULL;	// We do not have a HermesBuffer
//	BackBuffer=NULL;	// No BackBuffer
//	Primary=NULL;		// No PrimaryBuffer (which is alltimes visible)
//	dd=NULL;			// No DirectDrawObject
	bReady=false;
	InitWindow();	// Make the Window
	MessageManager::setInterface(this);
}


void All2DWin::init()
{
/*	if (InitSurfaces()!=DD_OK)
	{
		MessageBox(hWnd,"Fehler bei Surface Initialisierung!!","All3D-DirectX-Error", MB_OK);
		exit(0);
	}
	bReady=true;
	bActive=true;
	if (Hermes_Init()==0) ShowError (HERMES_INITFAIL);
	HermesConverter = Hermes_ConverterInstance(0) ;
*/
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

void All2DWin::All2D_Exit()
{
	//PostMessage(hWnd, WM_CLOSE, 0, 0);
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
//	bFullScreen=!bFullScreen;
//    sfml_window.close();
//    InitWindow();
}


// This is the Mainloop, where the Program (View) runs...
int All2DWin::MessageLoop()	//drawableElement.UpdateFrame () wird von Hier aufgerufen
{
/*	MSG		msg;
	static bool isExit=true;
	int newtime, lasttime;
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0 ))
			  break;
			// Translate and dispatch the message
			if (0 == TranslateAccelerator(hWnd,hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
			if (bActive && bReady)
			{ //                    Idle processing
				lasttime =GetTickCount();

				MessageManager::processEvents();

				isExit=MessageManager::paint(MakeBitMap()); 	//Creates a CBitmap of the Backbuffer, or the HermesBuffer
				CopyHermesToBackBuffer();										//Actualize the BackBuffer (if needed)
				Flip();

				if (!bFullScreen)
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
			else
			{   WaitMessage();   }
		}
	return msg.wParam;
*/
    sf::Texture txt;

    CBitMap* surface=new CBitMap(640,480);
    surface->Clear(0xffff00ff);
 //   surface->Load("data/All2D_UI.png");
    sf::Image img;
    surface->returnImage(img);
    //img.loadFromFile("data/All2d_UI.png");
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
            if (event.type == sf::Event::LostFocus){
                sfml_window.setTitle("LOST!");
            }
            if (event.type == sf::Event::GainedFocus){
                sfml_window.setTitle("Focused!");
            }

            Event* HAL_Event = new Event(0,0,0);
            if(event.type == sf::Event::MouseMoved){
                HAL_Event->Type=MM_MOUSEMOVE;
                HAL_Event->lData = event.mouseMove.y << 16 | event.mouseMove.x;
            }
            if(event.type == sf::Event::MouseButtonPressed){
                HAL_Event->Type=MM_LBUTTONDOWN;
                HAL_Event->lData = event.mouseButton.y << 16 | event.mouseButton.x;
            }

            MessageManager::handleOSMessages(HAL_Event);
        }
        MessageManager::processEvents();
        bool isExit=MessageManager::paint(surface);
        surface->returnImage(img);
        txt.loadFromImage(img);
        sfml_window.draw(sp);//,sf::BlendAdd);
        sfml_window.display();
    }
    return 0;
}



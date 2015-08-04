/*******************************************************************************
 * NativeTest.c - 1.0
 * implementation of the NativeTest class.
 * ----------------------------------------------------------------------------
 * author   Daniel Vorhauer
 * ----------------------------------------------------------------------------
 * HISTORY
 * 26.04.2001 18:22 - dav   created
 * 27.04.2001 22:00 - dav   added mem and screen check
 * 28.04.2001 12:21 - dav   added shell execute handling
 *
 ******************************************************************************/


//=== INCLUDE =================================================================

#include "NativeTest.h"
#include "../All2D/All2D_System.h"
#include <stdio.h>


//=== CONSTRUCTION / DESTRUCTION ==============================================

//NativeTest::FPSCounter;
// get most native attributes on construction to have the state
// closest to before the application was started

NativeTest::NativeTest(HWND hWnd)
{
	GlobalMemoryStatus(&memstat);
	//SystemParametersInfo(SPI_GETWORKAREA,0,&recScreen,0);

	hMainWnd = hWnd;

	HDC	dc = GetDC(hMainWnd);

	iBitsPixel = GetDeviceCaps( dc, BITSPIXEL );
	iScreenX = GetDeviceCaps( dc, HORZRES );
	iScreenY = GetDeviceCaps( dc, VERTRES );

	ReleaseDC( hMainWnd, dc );

}

NativeTest::~NativeTest()
{
	sndPlaySound( NULL, 0 );
}


//=== CODE ====================================================================

// return physical free mem from memorystatus structure
long NativeTest::GetFreeMem()
{
	return memstat.dwAvailPhys;
}

// return virtual free mem from memorystatus structure
long NativeTest::GetFreeUserMem()
{
	return memstat.dwAvailVirtual;
}

// return width of screen workarea
int NativeTest::GetDisplayX()
{
	return iScreenX;
}

// return height of screen workarea (without taskbar)
int NativeTest::GetDisplayY()
{
	return iScreenY;
}

// return bits per pixel for current screen setting
int NativeTest::GetBitsPerPixel()
{
	return iBitsPixel;
}

// execute given application
HINSTANCE NativeTest::StartApplication(char *acFile, char *acPars, char *acWDir, bool background)
{
	HWND lHWnd = 0;
	if (!background) lHWnd = hMainWnd;
	return ShellExecute(
		lHWnd,				// parent window handle
		"open",					// operation
    acFile,         // filename
    acPars,         // parameters
    acWDir,         // default working directory
		(background)?SW_SHOWNOACTIVATE:SW_SHOWNORMAL		// show command
	);
}
/*
#if defined(_DEBUG)
void NativeTest::Debug(Image *BackBuffer, int x, int y, char *sFPS)
{
  char sDebug[64];
  sprintf(sDebug,"Memory: %d MB (%d MB virtual)", GetFreeMem()/1024000, GetFreeUserMem()/1024000);
  All2D_System::smallFont.PrintAt(BackBuffer,x,y,sDebug,IMAGE_BLTMODE_TRANS);

  sprintf(sDebug,"Resolution %d x %d (%d-Bit)", GetDisplayX(), GetDisplayY(), GetBitsPerPixel());
  All2D_System::smallFont.PrintAt(BackBuffer,x,y+10,sDebug,IMAGE_BLTMODE_TRANS);

  All2D_System::smallFont.PrintAt(BackBuffer,x,y+20,sFPS,IMAGE_BLTMODE_TRANS);

	return;
}
#endif
*/
void NativeTest::PlaySound(const char *acFile, int iMode)
{
	if (iMode > 0) {
		sndPlaySound(acFile, SND_ASYNC | SND_NODEFAULT | SND_LOOP);
	} else {
		sndPlaySound(acFile, SND_ASYNC | SND_NODEFAULT);
	}
	return;
}

void NativeTest::ShellPrint(const char* acFile)
{
//	All2D_System::Debug.Printf0( "ShellExecuting 'print' with %s\n", acFile);

	// ACHTUNG! dirty cast from __HISTANCE * to long
	//long lRet = (long)ShellExecute(NULL, "print", acFile, NULL, "", 0);
//	long lRet = (long)ShellExecute(All2D_System::hWnd, "print", acFile, NULL, "", SW_SHOW);
	//long lRet = 0;

  if ( lRet <= 32 ) {

      #define MY_BUFSIZE 1024 // arbitrary. Use dynamic allocation
      HKEY hKey;
      static TCHAR far sz [MY_BUFSIZE];
      static TCHAR far args [MY_BUFSIZE];
      DWORD dwBufLen = MY_BUFSIZE;

      if (RegOpenKeyEx(HKEY_CLASSES_ROOT,
              TEXT("htmlfile\\shell\\open\\command"),
              0,
              KEY_QUERY_VALUE,
              &hKey) == ERROR_SUCCESS) {

          PCHAR pch, psz;

          lRet = RegQueryValueEx (hKey,
                      NULL,
                      NULL,
                      NULL,
                      (LPBYTE)sz,
                      &dwBufLen);

          RegCloseKey(hKey);

          // move program arguments to arguments
          args [0] = 0;
          strlwr (sz);
          psz = sz;
          pch = strstr (sz, ".exe");
          if (pch != NULL) {
              pch += 4;
              if (*pch == '"') {
                  psz++;
                  *pch = 0;
                  pch++;
              }
              strcpy (args, pch);
              strcat (args, " ");
              *pch = 0;
          }
          strcat (args, acFile);
//					System::Debug.Printf0 ("Printing with Browser %s the document: %s\n", psz, args);
          ShellExecute (NULL, "print", psz, args, "", SW_SHOW);
      }
  }

  return;

}

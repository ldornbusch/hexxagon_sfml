/*******************************************************************************
 * NativeTest.h - 1.0
 * interface for the NativeTest class.
 * ----------------------------------------------------------------------------
 * author   Daniel Vorhauer
 * ----------------------------------------------------------------------------
 * HISTORY
 * 26.04.2001 18:22 - dav   created
 * 27.04.2001 22:00 - dav   added mem and screen check
 * 28.04.2001 12:21 - dav   added shell execute handling
 * 
 ******************************************************************************/


//=== DEFINE ==================================================================
    
#if !defined(AFX_NATIVETEST_H__07D2785E_7746_477E_9D0A_C624C117E158__INCLUDED_)
#define AFX_NATIVETEST_H__07D2785E_7746_477E_9D0A_C624C117E158__INCLUDED_

#if _MSC_VER > 1000
  #pragma once
#endif // _MSC_VER > 1000


//=== INCLUDE =================================================================

#include <windows.h>
#if defined(_DEBUG)
#include "../All2D/All2D_Base/Image.h"
#endif


//=== CLASS ===================================================================

class NativeTest  
{
public:
	void ShellPrint(const char* acFile);
	void PlaySound(const char *acFile, int iMode=-1);
    HINSTANCE StartApplication(char *acFile, char *acPars, char *acWDir, bool background=false);
#if defined(_DEBUG)
    void Debug(Image *BackBuffer, int x, int y, char *sFPS);
#endif
    int GetBitsPerPixel();
    int GetDisplayX();
    int GetDisplayY();
    long GetFreeUserMem();
    long GetFreeMem();
    NativeTest(HWND hWnd);
    virtual ~NativeTest();

  private:
    HWND hMainWnd;
    int iBitsPixel;
		int iScreenX;
		int iScreenY;
    MEMORYSTATUS memstat;
};


#endif // !defined(AFX_NATIVETEST_H__07D2785E_7746_477E_9D0A_C624C117E158__INCLUDED_)

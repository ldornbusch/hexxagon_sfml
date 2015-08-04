//////////////////////////////////////////////////////////
// Program   : CDebug class implementation file
// Author    : Daniel Chirca
// Email     : D.Chirca@finsiel.ro
//////////////////////////////////////////////////////////

//#include "StdAfx.h"

#ifndef CDEBUG
	#include "CDebug.h"
#endif

#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

CDebug::CDebug()
{  
	strcpy(szBuffer,"");
	cpData.dwData = 0;
	cpData.cbData = 1;
	cpData.lpData = "\0";
	hWnd = NULL;
} 

CDebug::~CDebug()
{ 
}

BOOL CDebug::GetDebugWindowHandle()
{
	//find the Debug window
	hWnd = FindWindow(NULL, "Debug messages");
	
	if(!hWnd)
		return FALSE;
	else
		return TRUE;
}

BOOL CDebug::SendData()
{
	//set up a COPYDATASTRUCT structure for use with WM_COPYDATA
	cpData.dwData = (DWORD) nLevel;
	cpData.cbData = strlen(szBuffer) + 1;
	cpData.lpData = szBuffer;

	//send the structure to Debug via the system
	LRESULT lResult = SendMessage(hWnd, WM_COPYDATA, (UINT) NULL, (long) &cpData);

	if((BOOL) lResult == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDebug::Printf0(string szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	char szTmp[_MAX_PATH];
	strcpy(szTmp, szFormat.c_str());
	va_start(valist, szTmp);

	int nResult = wvsprintf(szBuffer,
													szFormat.c_str(),
													valist);
	
	va_end(valist);

	//szFormat.ReleaseBuffer();

	nLevel = 0;

	return SendData();
}

BOOL CDebug::Printf0(LPTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);
	va_end(valist);

	nLevel = 0;

	return SendData();
}

BOOL CDebug::Printf0(LPCTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 0;

	return SendData();
}

BOOL CDebug::Printf1(string szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	char szTmp[_MAX_PATH];
	strcpy(szTmp, szFormat.c_str());
	va_start(valist, szTmp);

	int nResult = wvsprintf(szBuffer,
													szFormat.c_str(),
													valist);
	
	va_end(valist);

	//szFormat.ReleaseBuffer();

	nLevel = 1;

	return SendData();
}

BOOL CDebug::Printf1(LPTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 1;

	return SendData();
}

BOOL CDebug::Printf1(LPCTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 1;

	return SendData();
}

BOOL CDebug::Printf2(string szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	char szTmp[_MAX_PATH];
	strcpy(szTmp, szFormat.c_str());
	va_start(valist, szTmp);

	int nResult = wvsprintf(szBuffer,
													szFormat.c_str(),
													valist);
	
	va_end(valist);
	//szFormat.ReleaseBuffer();

	nLevel = 2;

	return SendData();
}

BOOL CDebug::Printf2(LPTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 2;

	return SendData();
}

BOOL CDebug::Printf2(LPCTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 2;

	return SendData();
}

BOOL CDebug::Printf3(string szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	char szTmp[_MAX_PATH];
	strcpy(szTmp, szFormat.c_str());
	va_start(valist, szTmp);

	int nResult = wvsprintf(szBuffer,
													szFormat.c_str(),
													valist);
	
	va_end(valist);

	//szFormat.ReleaseBuffer();

	nLevel = 3;

	return SendData();
}

BOOL CDebug::Printf3(LPTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 3;

	return SendData();
}

BOOL CDebug::Printf3(LPCTSTR szFormat, ...)
{
	if(GetDebugWindowHandle() == FALSE) return FALSE;

	va_list valist;
	va_start(valist, szFormat);

	int nResult = wvsprintf(szBuffer,
													szFormat,
													valist);

	va_end(valist);

	nLevel = 3;

	return SendData();
}

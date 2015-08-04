// All2D_WinInterface.h: Schnittstelle für die Klasse All2D_WinInterface.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALL2D_WININTERFACE_H__4E387681_1199_11D6_B047_00E098802DF2__INCLUDED_)
#define AFX_ALL2D_WININTERFACE_H__4E387681_1199_11D6_B047_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// pre-declaration
class AppGameController;

class  All2D_WinInterface
{
public:
	virtual	void init()=0;
	virtual int startApp(AppGameController& dE)=0;
	virtual void setFullscreen(bool blnFlag)=0;
	virtual void All2D_Exit()=0;
//	virtual ~All2D_WinInterface()=0;
};

#endif // !defined(AFX_ALL2D_WININTERFACE_H__4E387681_1199_11D6_B047_00E098802DF2__INCLUDED_)

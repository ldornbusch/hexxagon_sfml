// All2D_WinInterface.h: Schnittstelle f�r die Klasse All2D_WinInterface.
//
//////////////////////////////////////////////////////////////////////

#pragma once


// pre-declaration
class AppGameController;

class  All2D_WinInterface
{
public:
	virtual	void init()=0;
	virtual int startApp(AppGameController& dE)=0;
	virtual void setFullscreen(bool blnFlag)=0;
	virtual void All2D_Exit()=0;
	virtual ~All2D_WinInterface(){} ;
};

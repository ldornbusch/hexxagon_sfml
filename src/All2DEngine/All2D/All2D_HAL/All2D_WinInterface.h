// All2D_WinInterface.h: Schnittstelle für die Klasse All2D_WinInterface.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "../../utils/Rect.h"
#include "../../utils/Point.h"
#include "../All2D_Events/Event.h"
// pre-declaration
class AppGameController;

class  All2D_WinInterface
{
public:
	virtual	void init()=0;
	virtual int startApp(AppGameController& dE)=0;
	virtual void setFullscreen(bool blnFlag)=0;
	virtual void setSmooth(bool blnSmooth)=0;
    virtual Rect getWindowPosition()=0;
    virtual void transformMouseCoords(Event *evt)=0;
	virtual void All2D_Exit()=0;
	virtual ~All2D_WinInterface(){} ;
};

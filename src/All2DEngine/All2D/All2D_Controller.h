// All2D_Controller.h: Interface for all Controllers
//////////////////////////////////////////////////////////////////////

#pragma once

#include "All2D_Base/xContainer.h"
#include "All2D_Events/MessageManager.h"

class All2D_Controller : public xContainer
{
public:
    All2D_Controller(std::string name);
    ~All2D_Controller();
  // container functions
	virtual void  requestLoad(){};
	virtual void  updateProgress(int){};
	virtual bool  handleEvent(Event* evt);
	virtual bool  paint(Image& backBuffer)=0;
	virtual void  init();
    virtual bool masterPaint(Image& backBuffer);
protected:
   	Image imgFrameBuffer;
   	bool isExit = false;
   	bool isFullscreen = false;

};

// predefine All2Ds entrypoints
bool All2D_init(int xres, int yres, std::string WinTitle);
int All2D_main(All2D_Controller& ctrl);


#include "All2D_Controller.h"
#include "All2D_System.h"



All2D_Controller::All2D_Controller(std::string name) :xContainer("name"){
	imgFrameBuffer.resize(All2D_System::fixedX,All2D_System::fixedY);
	requestLoad();
}
All2D_Controller::~All2D_Controller(){
    imgFrameBuffer.finish();
}

void All2D_Controller::init()
{
    // init sound engine instance
	All2D_System::sound->init();
}

bool All2D_Controller::masterPaint(Image& backBuffer)
{
    bool retVal=false;
    retVal=paint(backBuffer);
    All2D_System::spriteManager.paint(backBuffer);
    All2D_System::spriteManager.clear();
    return retVal;
}

bool All2D_Controller::handleEvent(Event *evt)
{
    switch (evt->Type)
    {
        case MM_KEYDOWN:
        {
            char a=(char)evt->wData;
            switch (a) {
                case sf::Keyboard::BackSpace:
                case sf::Keyboard::Escape:
                case sf::Keyboard::F12:
                    isExit = true;
                break;
                case sf::Keyboard::F:
                    isFullscreen=!isFullscreen;
                    MessageManager::handleEvent(new Event(MM_SETFULLSCREEN,(int)isFullscreen,0));
				break;

            default:
                break;
                }
        }
        break;
        default:
            break;
    }
    return xContainer::handleEvent(evt);
}


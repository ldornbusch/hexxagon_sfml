// UIButton.cpp: Implementierung der Klasse UIButton.
//
//////////////////////////////////////////////////////////////////////

#include "UIButton.h"
#include "../All2D/All2D_Events/MessageManager.h"
#include "../All2D/All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UIButton::UIButton() {
	isClicked=false;

	sendFlag=MM_BUTTON_CLICK;
	sendWord=getID();;
	sendLong=0;

}

UIButton::~UIButton() {

}

bool UIButton::getStatus() {
	return isClicked;
}

bool UIButton::handleEvent(Event *evt)
{
	Point p;
	bool retVal=true;
	if (enabled) {
		switch (evt->Type) {
			case MM_MOUSEMOVE:
				// set mouseIn according to focus, check if it is relative, or absolute positioned
				p=All2D_System::extractMouseCoords(evt);
				if ( isInside(p.x,p.y) )
				{
					mouseIn=true;
				} else {
					// hover out event ???
					mouseIn=false;
				}
				break;

			case MM_LBUTTONDOWN:
				p=All2D_System::extractMouseCoords(evt);
				if( isInside(p.x, p.y) ) {
					isClicked=true;
					fire();
					leftClick();
					retVal=false;
				}
				break;

			case MM_RBUTTONDOWN:
				p=All2D_System::extractMouseCoords(evt);
				if( isInside(p.x, p.y) ) {
					isClicked=true;
					fire();
					rightClick();
					retVal=false;
				}
				break;

			case MM_LBUTTONUP:
			case MM_RBUTTONUP:
				isClicked=false;
				break;
		}
	}
	return retVal;

}
void UIButton::setSendFlag(int i, unsigned int w, long l)
{
	sendFlag=i;
	sendWord=w;
	sendLong=l;
}

void UIButton::rightClick()
{

}

void UIButton::leftClick()
{

}

void UIButton::fire()
{
	if (sendFlag!=0) {
		Event* tmp=new Event(sendFlag,sendWord,sendLong);
		MessageManager::handleEvent(tmp);
//		All2D_System::Debug.Printf0("Sending Click Event %d, %d, %d", sendFlag, sendWord, sendLong );
	//						All2D_System::Local.PlaySound( FILE_CLICK_SOUND );
	}
}

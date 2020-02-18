// UIKeyRecorder.cpp: Implementierung der Klasse UIKeyRecorder.
//
//////////////////////////////////////////////////////////////////////

#include "UIKeyRecorder.h"
#include "../All2D/All2D_System.h"
#include "../All2D/All2D_Events/MessageManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
// static elements

UIKeyRecorder::UIKeyRecorder():evtRecordedKey(0,0,0)
{
	blnActive=false;
	setFont(All2D_System::SystemFont);
	setBlitMode(IMAGE_BLTMODE_HALF);
	setHoverBlitMode(IMAGE_BLTMODE_ADD);
	deleteKey();
}

UIKeyRecorder::UIKeyRecorder(string strDefaultKey, Event* evtKeyVal):evtRecordedKey(0,0,0)
{
	blnActive=false;
	setFont(All2D_System::SystemFont);
	setBlitMode(IMAGE_BLTMODE_HALF);
	setHoverBlitMode(IMAGE_BLTMODE_ADD);
	KeyName=strDefaultKey;
	setRecordedKey(evtKeyVal);
}

UIKeyRecorder::~UIKeyRecorder()
{
}
// returns the recorded Event
Event* UIKeyRecorder::getRecordedKey()
{
	return &evtRecordedKey;
}

void UIKeyRecorder::setFont(ImageText &newFont)
{
	fntFont.cloneFont(newFont);
}

// handle Event..only when active it handles anything
bool UIKeyRecorder::handleEvent(Event *evt)
{
	bool retVal=true;
	//UIButton::handleEvent(evt);
	if (evt->Type==MM_KEYRECORDERACTIVE && (unsigned int)evt->lData!=getID())	// if one KeyRecorder is Active, any other should be inactive
		setActive(false);

	if (evt->Type==MM_KEYRECORDERSET && (unsigned int)evt->lData!=getID() && evt->wData==evtRecordedKey.wData)	// if another KeyRecorder has the same Key, delete it here..
		deleteKey();

	if (blnActive)
	{
		switch(evt->Type)
		{
		case MM_LBUTTONDOWN:
			{
				Point p=All2D_System::extractMouseCoords(evt);
				if (!isInside(p.x,p.y) )
				{
					setActive(false);
				}
			}
			break;
			case MM_KEYDOWN:
				setRecordedKey(evt);
				setActive(false);
				break;
			default:
				break;
		}
	}
	UIHoverButton::handleEvent(evt);
	return retVal;
}
// sets Active(Record)
void UIKeyRecorder::setActive(bool blnFlag)
{
	blnActive=blnFlag;
	if (blnActive)
		MessageManager::handleEvent(new Event(MM_KEYRECORDERACTIVE, blnActive ,getID()));
	if (blnActive && KeyName!="") // Wenn aktiviert wird, alten Namen der Taste merken
	{
		strOldName=KeyName;
		Image::clear();
		KeyName="";
	}
	if (!blnActive && strOldName!="")
	{
		KeyName=strOldName;
		strOldName="";
		writeName();

	}
}
// returns active Status(RecordStatus)
bool UIKeyRecorder::getActive()
{
	return blnActive;
}
string UIKeyRecorder::getName()
{
	return UIHoverButton::getName();
}
value UIKeyRecorder::getValue()
{
	return value("",evtRecordedKey.wData);
}

void UIKeyRecorder::setValue(value val)
{
    Event tmp(MM_KEYDOWN,(unsigned int)val.second,0);
	setRecordedKey(&tmp);

}

// copys the Event to its internal Compare-Event
void UIKeyRecorder::setRecordedKey(Event* evt)
{
	evtRecordedKey.Type=evt->Type;
	evtRecordedKey.lData=evt->lData;
	evtRecordedKey.wData=evt->wData;
	MessageManager::handleEvent(new Event(MM_KEYRECORDERSET,evt->wData, getID()));	// andere Keyrecorder benachrichtigen...
	KeyName=translateMessage2KeyName(evt->wData);
	strOldName="";
	writeName();
}
void UIKeyRecorder::writeName()
{
    int minSize = KeyName.length(); // if key was not found the width would be zero.. not possible to click..
    if (minSize < 1){
        minSize = 4;
    }
	int wid=fntFont.getFontWidth() * minSize;
	int hei=fntFont.getFontHeight();
	this->resize(wid, hei);
	fntFont.PrintAt(*this,0,0,KeyName.c_str());
	setHoverImage(*this);
}
void UIKeyRecorder::deleteKey()
{
	evtRecordedKey.Type=0;
	evtRecordedKey.wData=0;
	evtRecordedKey.lData=0;
	KeyName="[NO KEY]";
	writeName();
}

// returns, if the Event is the same key than the recorded one..
bool UIKeyRecorder::isPressedKey(Event *evt)
{
	bool retVal=false;
	if ((evt->Type== evtRecordedKey.Type) &&
		 (evt->wData==evtRecordedKey.wData))
		 retVal=true;
	return retVal;
}

void UIKeyRecorder::fire()
{
	setActive(true);
}

void UIKeyRecorder::leftClick()
{
	fire();
}

// translate specialKeys to descriptive Strings..
string UIKeyRecorder::translateMessage2KeyName(unsigned int wData)
{
	string retVal="";
	if (wData>=sf::Keyboard::A && wData<=sf::Keyboard::Z){
        retVal=((unsigned char)'A')+wData;
	}
	if (wData>=sf::Keyboard::Num0 && wData<=sf::Keyboard::Num9){
        retVal=((unsigned char)'0')+wData;
	}
	switch(wData)
	{
		case sf::Keyboard::Space:
			retVal="[SPACE]";
			break;
		case sf::Keyboard::Return:
			retVal="[RETURN]";
			break;
		case sf::Keyboard::Tab:
			retVal="[TAB]";
			break;
		case VK_SCROLL:
			retVal="[SCROLL LOCK]";
			break;
		case VK_NUMLOCK:
			retVal="[NUM LOCK]";
			break;
		case sf::Keyboard::Pause:
			retVal="[PAUSE]";
			break;
		case sf::Keyboard::BackSpace:
			retVal="[BACK]";
			break;

		case sf::Keyboard::Up:
			retVal="[UP]";
			break;
		case sf::Keyboard::Down:
			retVal="[DOWN]";
			break;
		case sf::Keyboard::Left:
			retVal="[LEFT]";
			break;
		case sf::Keyboard::Right:
			retVal="[RIGHT]";
			break;
		case sf::Keyboard::Escape:
			retVal="[ESC]";
			break;
		case sf::Keyboard::Insert:
			retVal="[INS]";
			break;
		case sf::Keyboard::Delete:
			retVal="[DEL]";
			break;
		case sf::Keyboard::Home:
			retVal="[HOME]";
			break;
		case sf::Keyboard::End:
			retVal="[END]";
			break;
		case sf::Keyboard::PageUp:
			retVal="[PAGE UP]";
			break;
		case sf::Keyboard::PageDown:
			retVal="[PAGE DOWN]";
			break;

		case sf::Keyboard::LAlt:
		case sf::Keyboard::RAlt:
			retVal="[ALT]";
			break;
		case sf::Keyboard::LShift:
		case sf::Keyboard::RShift:
			retVal="[SHIFT]";
			break;
		case VK_CAPITAL :
			retVal="[CAPS LOCK]";
			break;
		case sf::Keyboard::LControl:
		case sf::Keyboard::RControl:
			retVal="[CTRL]";
			break;

		case sf::Keyboard::Numpad0:
			retVal="[NUM 0]";
			break;
		case sf::Keyboard::Numpad1:
			retVal="[NUM 1]";
			break;
		case sf::Keyboard::Numpad2:
			retVal="[NUM 2]";
			break;
		case sf::Keyboard::Numpad3:
			retVal="[NUM 3]";
			break;
		case sf::Keyboard::Numpad4:
			retVal="[NUM 4]";
			break;
		case sf::Keyboard::Numpad5:
			retVal="[NUM 5]";
			break;
		case sf::Keyboard::Numpad6:
			retVal="[NUM 6]";
			break;
		case sf::Keyboard::Numpad7:
			retVal="[NUM 7]";
			break;
		case sf::Keyboard::Numpad8:
			retVal="[NUM 8]";
			break;
		case sf::Keyboard::Numpad9:
			retVal="[NUM 9]";
			break;
		case sf::Keyboard::Multiply:
			retVal="[NUM *]";
			break;
		case sf::Keyboard::Add:
			retVal="[NUM +]";
			break;
/*		case VK_SEPARATOR:
			retVal="[NUM ,]";
			break;
*/		case sf::Keyboard::Subtract:
			retVal="[NUM -]";
			break;
		case sf::Keyboard::Period:
			retVal="[NUM ,]";
			break;
		case sf::Keyboard::Divide:
			retVal="[NUM /]";
			break;
		case sf::Keyboard::F1:
			retVal="[F1]";
			break;
		case sf::Keyboard::F2:
			retVal="[F2]";
			break;
		case sf::Keyboard::F3:
			retVal="[F3]";
			break;
		case sf::Keyboard::F4:
			retVal="[F4]";
			break;
		case sf::Keyboard::F5:
			retVal="[F5]";
			break;
		case sf::Keyboard::F6:
			retVal="[F6]";
			break;
		case sf::Keyboard::F7:
			retVal="[F7]";
			break;
		case sf::Keyboard::F8:
			retVal="[F8]";
			break;
		case sf::Keyboard::F9:
			retVal="[F9]";
			break;
		case sf::Keyboard::F10:
			retVal="[F10]";
			break;
		case sf::Keyboard::F11:
			retVal="[F11]";
			break;
		case sf::Keyboard::F12:
			retVal="[F12]";
			break;
	}
	return retVal;
}

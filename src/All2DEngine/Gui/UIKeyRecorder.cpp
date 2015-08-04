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
	if (evt->Type==MM_KEYRECORDERACTIVE && evt->lData!=getID())	// if one KeyRecorder is Active, any other should be inactive
		setActive(false);

	if (evt->Type==MM_KEYRECORDERSET && evt->lData!=getID() && evt->wData==evtRecordedKey.wData)	// if another KeyRecorder has the same Key, delete it here..
		deleteKey();

	if (blnActive)
	{
		switch(evt->Type)
		{
		case MM_LBUTTONDOWN:
			{
				Point p=All2D_System::getMouseCoords(evt);
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
	return true;
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
    Event tmp(MM_KEYDOWN,val.second,0);
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
	int wid=fntFont.getFontWidth()*KeyName.length();
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
string UIKeyRecorder::translateMessage2KeyName(int wData)
{
	string retVal="";
	retVal+=(char)wData;
	switch(wData)
	{
		case VK_SPACE:
			retVal="[SPACE]";
			break;
		case VK_RETURN:
			retVal="[RETURN]";
			break;
		case VK_TAB:
			retVal="[TAB]";
			break;
		case VK_SCROLL:
			retVal="[SCROLL LOCK]";
			break;
		case VK_NUMLOCK:
			retVal="[NUM LOCK]";
			break;
		case VK_PAUSE:
			retVal="[PAUSE]";
			break;
		case VK_BACK:
			retVal="[BACK]";
			break;

		case VK_UP:
			retVal="[UP]";
			break;
		case VK_DOWN:
			retVal="[DOWN]";
			break;
		case VK_LEFT:
			retVal="[LEFT]";
			break;
		case VK_RIGHT:
			retVal="[RIGHT]";
			break;
		case VK_ESCAPE:
			retVal="[ESC]";
			break;

		case VK_INSERT:
			retVal="[INS]";
			break;
		case VK_DELETE:
			retVal="[DEL]";
			break;
		case VK_HOME:
			retVal="[HOME]";
			break;
		case VK_END:
			retVal="[END]";
			break;
		case VK_PRIOR :
			retVal="[PAGE UP]";
			break;
		case VK_NEXT :
			retVal="[PAGE DOWN]";
			break;

		case VK_MENU :
			retVal="[ALT]";
			break;
		case VK_SHIFT :
			retVal="[SHIFT]";
			break;
		case VK_CAPITAL :
			retVal="[CAPS LOCK]";
			break;
		case VK_CONTROL  :
			retVal="[CTRL]";
			break;

		case VK_NUMPAD0:
			retVal="[NUM 0]";
			break;
		case VK_NUMPAD1:
			retVal="[NUM 1]";
			break;
		case VK_NUMPAD2:
			retVal="[NUM 2]";
			break;
		case VK_NUMPAD3:
			retVal="[NUM 3]";
			break;
		case VK_NUMPAD4:
			retVal="[NUM 4]";
			break;
		case VK_NUMPAD5:
			retVal="[NUM 5]";
			break;
		case VK_NUMPAD6:
			retVal="[NUM 6]";
			break;
		case VK_NUMPAD7:
			retVal="[NUM 7]";
			break;
		case VK_NUMPAD8:
			retVal="[NUM 8]";
			break;
		case VK_NUMPAD9:
			retVal="[NUM 9]";
			break;
		case VK_MULTIPLY:
			retVal="[NUM *]";
			break;
		case VK_ADD:
			retVal="[NUM +]";
			break;
/*		case VK_SEPARATOR:
			retVal="[NUM ,]";
			break;
*/		case VK_SUBTRACT:
			retVal="[NUM -]";
			break;
		case VK_DECIMAL:
			retVal="[NUM ,]";
			break;
		case VK_DIVIDE:
			retVal="[NUM /]";
			break;
		case VK_F1:
			retVal="[F1]";
			break;
		case VK_F2:
			retVal="[F2]";
			break;
		case VK_F3:
			retVal="[F3]";
			break;
		case VK_F4:
			retVal="[F4]";
			break;
		case VK_F5:
			retVal="[F5]";
			break;
		case VK_F6:
			retVal="[F6]";
			break;
		case VK_F7:
			retVal="[F7]";
			break;
		case VK_F8:
			retVal="[F8]";
			break;
		case VK_F9:
			retVal="[F9]";
			break;
		case VK_F10:
			retVal="[F10]";
			break;
		case VK_F11:
			retVal="[F11]";
			break;
		case VK_F12:
			retVal="[F12]";
			break;
	}
	return retVal;
}

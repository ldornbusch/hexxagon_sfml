// GameMessageClass.cpp: implementation of the GameMessageClass class.
//
//////////////////////////////////////////////////////////////////////

#include "GameMessageBox.h"
#include "../All2DEngine/All2D/All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GameMessageBox::GameMessageBox():xContainer("MessageBox")
{
	isVisible=false;
	strMessage="No Msg Configured";
	KbdNavigator.setMaxEntry(1);
	KbdNavigator.setMaxEntry(2);
	KbdNavigator.setMenuDirection(false);
	setBackgroundColor(0x2C4EB9);
}

GameMessageBox::~GameMessageBox()
{

}

void GameMessageBox::activate(bool blnFlag)
{
	isVisible=blnFlag;
}

void GameMessageBox::setYesButton(UIHoverButton& yes)
{
	btnYes=yes;
}

void GameMessageBox::setNoButton(UIHoverButton& no)
{
	btnNo=no;
}

void GameMessageBox::setFont(ImageText &font)
{
	TextFont.cloneFont(font);
	setMessage(strMessage);
}

void GameMessageBox::setMessage(string strText)
{
	strMessage=strText;
	if (TextFont.getBitMap()!=NULL){
        int lenx=(strText.length())*TextFont.getFontWidth()+2*10+5;
        int leny=7*TextFont.getFontHeight();
        if (lenx<(2*10+5+btnYes.getPosition().x2+btnNo.getPosition().x2))	// mindestbreite: so breit wie die Buttons+rand(10 px)!
            lenx=2*10+5+btnYes.getPosition().y2+btnNo.getPosition().y2;
        if (lenx>620)// 2DO: WordWrap!
        {
    //		strMessage.substr();
        }
        sprtBackground.resize(lenx,leny);
        sprtTextBuffer.resize(lenx,leny);
        ((Image*)&sprtBackground)->clear(iBackGroundColor);
	}
}

void GameMessageBox::setYesEvent(Event evt)
{
	btnYes.setSendFlag(evt.Type, evt.wData, evt.lData);
}

bool GameMessageBox::paint(Image& imgBackBuffer)
{
	if (isVisible)
	{
		int x1=(imgBackBuffer.getWidth()-sprtBackground.getWidth())/2;
		int y1=(imgBackBuffer.getHeight()-sprtBackground.getHeight())/2;
		TextFont.PrintCenter(sprtTextBuffer,2*TextFont.getFontHeight(),strMessage.c_str());
		sprtBackground.setPosition(x1,y1);
		sprtTextBuffer.setPosition(x1,y1);
		sprtBackground.show(imgBackBuffer,IMAGE_BLTMODE_HALF);
		sprtTextBuffer.show(imgBackBuffer,IMAGE_BLTMODE_TRANS);

		btnYes.setPosition(Rect(x1+10,y1+sprtBackground.getHeight()-btnYes.getPosition().y2-10));
		btnNo.setPosition(Rect(x1+sprtBackground.getWidth() -btnNo.getPosition().x2-10,
						   y1+sprtBackground.getHeight()-btnNo.getPosition().y2-10));
		xContainer::paint(imgBackBuffer);
	}
	return true;
}

bool GameMessageBox::handleEvent(Event *evt)
{
	bool retVal=!isVisible;
	if (isVisible)
	{
		if (KbdNavigator.handleEvent(evt))
		{
			getMenuButton(KbdNavigator.getLastEntry()).setHoverStatus(false);
			getMenuButton(KbdNavigator.getActualEntry()).setHoverStatus(true);
		}

		xContainer::handleEvent(evt);

		if (evt->Type==MM_NAVIGATION_HOVER){
			// Wenn die Maus bewegt wird, muss der aktuelle(Mausgewaehlte Eintrag auch dem KeyboardNavigator mitgeteilt werden..)
			getMenuButton(KbdNavigator.getActualEntry()).setHoverStatus(false);
			KbdNavigator.setActualEntry(evt->wData);
		}
		if (evt->Type==MM_FIRE||(evt->Type==MM_KEYDOWN && evt->wData==VK_RETURN))
			menuSelect();

		if (btnYes.getStatus() || btnNo.getStatus())
		{
			isVisible=false;
			Event tmp(MM_MOUSEMOVE,0,0);
			xContainer::handleEvent(&tmp);	// kein Hover mehr auf den Buttons(die werden ja nun abgeschaltet
            Event tmp2(MM_LBUTTONUP,0,0);
			xContainer::handleEvent(&tmp2);	// Button wieder up.. damit er nicht mehr getState==true liefert..
		}
	}return (retVal);		// Stoppt nach diesem xElement, das HandleRouting, falls die MsgBox sichtbar ist
}

void GameMessageBox::menuSelect()
{
	getMenuButton(KbdNavigator.getActualEntry()).fire();
}

UIHoverButton& GameMessageBox::getMenuButton(int index)
{
	switch(index)
	{
		case 1:
			return btnYes;
		case 2:
		default:
			return btnNo;
	}
}
/*
void GameMessageBox::getGFX(Image& imgGFX)
{

	Image tmp;
	tmp.cloneImage(imgGFX);

	TextFont.cloneImage(imgGFX,Rect(224,208,80,64));
	TextFont.FontInit(16,16,10,"ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789:[]_@.-+*$%§!");

	tmp.setSrcRect(Rect(112,368,80,32));
	btnYes.cloneImage(tmp);
	btnYes.setHoverImage(tmp);
	btnYes.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnYes.setHoverFlag(MM_NAVIGATION_HOVER,1);
	btnYes.setBlitMode(IMAGE_BLTMODE_HALF);
	btnYes.setPosition(Rect(240,120,80,32));
	btnYes.setSendFlag(0,0,0);
	add(btnYes);

	tmp.setSrcRect((112,336,55,32));
	btnNo.cloneImage(tmp);
	btnNo.setHoverImage(tmp);
	btnNo.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnYes.setHoverFlag(MM_NAVIGATION_HOVER,2);
	btnNo.setBlitMode(IMAGE_BLTMODE_HALF);
	btnNo.setPosition(Rect(240,160,55,32));
	btnNo.setSendFlag(MM_KEYDOWN,VK_ESCAPE,0);
	add(btnNo);

	setMessage("ARE YOU SURE?");	// 2DO: FontExtension..

}
*/

void GameMessageBox::init()
{
	setFont(All2D_System::SystemFont);
	btnYes.cloneImage(All2D_System::UIElements);
	btnNo.cloneImage(All2D_System::UIElements);
	btnYes.setSrcRect(Rect(64,0,32,16));
	btnNo.setSrcRect(Rect(128,0,32,16));
	btnYes.setPosition(Rect(0,0,32,16));
	btnNo.setPosition(Rect(0,0,32,16));
	btnYes.setHoverImage(btnYes);
	btnNo.setHoverImage(btnNo);
	btnYes.setHoverBlitMode(IMAGE_BLTMODE_ADD);
	btnNo.setHoverBlitMode(IMAGE_BLTMODE_ADD);

	setMessage("Are You Sure?");
	add(btnYes);
	add(btnNo);
}

void GameMessageBox::setPriority(int prio)
{
	sprtBackground.setPriority(prio);
	sprtTextBuffer.setPriority(prio);
	btnYes.setPriority(prio);
	btnNo.setPriority(prio);
}

void GameMessageBox::setBackgroundColor(int iCol)
{
	iBackGroundColor=iCol;
	setMessage(strMessage);
}

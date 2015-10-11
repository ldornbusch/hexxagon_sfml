// RadioButton.cpp: Implementierung der Klasse UIRadioButton.
//
//////////////////////////////////////////////////////////////////////

#include "UIRadioButton.h"
#include "../All2D/All2D_Events/MessageManager.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UIRadioButton::UIRadioButton()
{
	setUncheckArea(Rect(0,8,8,8));
	setCheckArea(Rect(8,8,8,8));
	setValue(value("",0));
}

UIRadioButton::UIRadioButton(int radioID)
{
	UIRadioButton();
	setRadioID(radioID);
}

UIRadioButton::~UIRadioButton()
{

}

unsigned int UIRadioButton::getRadioID()
{
	return iRadioID;
}
void UIRadioButton::setRadioID(unsigned int iID)
{
	iRadioID=iID;
}
unsigned int UIRadioButton::getRadioGroup()
{
	return iRadioGroup;
}
void UIRadioButton::setRadioGroup(unsigned int iGroup)
{
	iRadioGroup=iGroup;
}


void UIRadioButton::leftClick()
{
	//UICheckBox::leftClick();
	MessageManager::handleEvent(new Event(MM_RADIO_SET_VALUE,getRadioGroup(),getRadioID()));
}

bool UIRadioButton::handleEvent(Event *evt)
{
	if (evt->Type==MM_RADIO_SET_VALUE &&
		evt->wData==getRadioGroup())
		UICheckBox::setValue(value("",(evt->lData==getRadioID()?1:0)));
	return UICheckBox::handleEvent(evt);
}

// RadioButton.h: Schnittstelle für die Klasse UIRadioButton.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UICheckBox.h"

class UIRadioButton : public UICheckBox
{
public:
	virtual bool handleEvent(Event* evt);
	virtual void leftClick();
	void setRadioID(unsigned int iID);
	unsigned int getRadioID();
	void setRadioGroup(unsigned int iGroup);
	unsigned int getRadioGroup();
	UIRadioButton();
	UIRadioButton(int radioID);
	virtual ~UIRadioButton();

private:
	unsigned int iRadioID;
protected:
	unsigned int iRadioGroup;
};

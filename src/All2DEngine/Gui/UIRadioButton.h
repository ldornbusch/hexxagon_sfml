// RadioButton.h: Schnittstelle für die Klasse UIRadioButton.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADIOBUTTON_H__BF0E5177_8BD3_448E_B701_C58FD8FFA17F__INCLUDED_)
#define AFX_RADIOBUTTON_H__BF0E5177_8BD3_448E_B701_C58FD8FFA17F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_RADIOBUTTON_H__BF0E5177_8BD3_448E_B701_C58FD8FFA17F__INCLUDED_)

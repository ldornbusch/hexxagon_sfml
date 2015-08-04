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
	void setRadioID(int iID);
	int getRadioID();
	void setRadioGroup(int iGroup);
	int getRadioGroup();
	UIRadioButton();
	UIRadioButton(int radioID);
	virtual ~UIRadioButton();

private:
	int iRadioID;
protected:
	int iRadioGroup;
};

#endif // !defined(AFX_RADIOBUTTON_H__BF0E5177_8BD3_448E_B701_C58FD8FFA17F__INCLUDED_)

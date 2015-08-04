// UICheckBox.h: Schnittstelle für die Klasse UICheckBox.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UICHECKBOX_H__4FBEBA1C_4696_43C1_B2AE_EAE325F0225B__INCLUDED_)
#define AFX_UICHECKBOX_H__4FBEBA1C_4696_43C1_B2AE_EAE325F0225B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\ALL2DENGINE\GUI\UIHoverButton.h"
#include "hasvalue.h"

class UICheckBox : public UIHoverButton, public hasValue   
{
public:
	string getName();
	value getValue();
	void setValue(value val);

	void setUncheckArea(Rect rct);
	void setCheckArea(Rect rct);
	virtual bool paint(Image& backBuffer);
	virtual void setSrcRect(Rect tmp);
	virtual void leftClick();
	UICheckBox();
	UICheckBox(bool flag);
	virtual ~UICheckBox();
	
private:
	Rect rctCheckedArea;
	Rect rctUncheckedArea;
	bool blnChecked;
};

#endif // !defined(AFX_UICHECKBOX_H__4FBEBA1C_4696_43C1_B2AE_EAE325F0225B__INCLUDED_)

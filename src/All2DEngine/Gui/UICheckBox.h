// UICheckBox.h: Schnittstelle für die Klasse UICheckBox.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UIHoverButton.h"
#include "hasValue.h"

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

// UIKeyRecorder.h: Schnittstelle für die Klasse UIKeyRecorder.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIKEYRECORDER_H__2733B3A1_1366_11D6_B047_00E098802DF2__INCLUDED_)
#define AFX_UIKEYRECORDER_H__2733B3A1_1366_11D6_B047_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIHoverButton.h"
#include "hasValue.h"
#include "../All2D/All2D_Base/ImageText.h"

class UIKeyRecorder : public UIHoverButton, public hasValue
{
public:
	string getName();
	value getValue();
	void setValue(value val);

	void setFont(ImageText& newFont);
	void deleteKey();
	virtual void fire();
	virtual void leftClick();
	void setRecordedKey(Event* evt);
	bool isPressedKey(Event* evt);
	bool getActive();
	void setActive(bool blnFlag);
	bool handleEvent(Event* evt);
	Event* getRecordedKey();
	string KeyName;
	UIKeyRecorder();
	UIKeyRecorder(string strDefaultKey, Event* evtKeyVal);
	virtual ~UIKeyRecorder();

private:
	string strOldName;
//	bool blnIsKey;
	bool blnActive;
	Event evtRecordedKey;
	ImageText fntFont;
protected:
	void writeName();
	string translateMessage2KeyName(int wData);
};

#endif // !defined(AFX_UIKEYRECORDER_H__2733B3A1_1366_11D6_B047_00E098802DF2__INCLUDED_)

// UITextField.h: Schnittstelle für die Klasse UITextField.
// 07.03.2003: Support for BackgroundColor, CursorColor,
//			   BlinkFrequence
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UITEXTFIELD_H__11ECF891_9F5D_4777_86E0_119FEF4FB571__INCLUDED_)
#define AFX_UITEXTFIELD_H__11ECF891_9F5D_4777_86E0_119FEF4FB571__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../All2D/All2D_Sprites/UISprite.h"
#include "../All2D/All2D_Sprites/UIElement.h"
#include "hasValue.h"

class UITextField : public UISprite, public hasValue
{
public:
	string getName();
	void setValue(value val);
	value getValue();

	int getHeight();
	int getWidth();
	virtual bool isInside(int x, int y);
	virtual void finish();
	void setPriority(int prio);
	void setSize(int newSize);
	virtual bool paint(Image& img);				// And Calls this Paint with the Image backBufferImage
	virtual bool handleEvent(Event* evt);
	void setActive(bool flag);
	void setTabOrder(int n);
	int getTabOrder();
	void setFocus();

	UITextField();
	UITextField(int size, string val="");
	virtual ~UITextField();

	int ActiveBackground;
	int inActiveBackground;
	int CursorColor;
	int BlinkFreq;
protected:
	void addChar(char a);
	unsigned int	iSize;
	bool isActive;
	string actualString;
	int iTabOrder;

private:
	void initTextBuffer();
	UISprite* TextBuffer;
};

#endif // !defined(AFX_UITEXTFIELD_H__11ECF891_9F5D_4777_86E0_119FEF4FB571__INCLUDED_)

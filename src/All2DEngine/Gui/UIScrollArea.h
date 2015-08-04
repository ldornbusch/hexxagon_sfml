// UIScrollArea.h: interface for the UIScrollArea class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UISCROLLAREA_H__3171A3F1_1917_4F1A_B847_8C4DE574607D__INCLUDED_)
#define AFX_UISCROLLAREA_H__3171A3F1_1917_4F1A_B847_8C4DE574607D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ALL2D\ALL2D_SPRITES\UISprite.h"
#include "hasValue.h"

class UIScrollArea : public UISprite , public hasValue 
{
public:
	bool	handleEvent(Event* evt);
	bool	paint(Image& backBuffer);
	void	setFont(ImageText& fnt);
	string getName();
	void setValue(value val);
	value getValue();
	UIScrollArea();
	virtual ~UIScrollArea();

private:
	ImageText fntFont;

};

#endif // !defined(AFX_UISCROLLAREA_H__3171A3F1_1917_4F1A_B847_8C4DE574607D__INCLUDED_)

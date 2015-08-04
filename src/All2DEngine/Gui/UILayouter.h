// UILayouter.h: Schnittstelle für die Klasse UILayouter.
// UILayouter regelt die Positionierung von UIElementen.
// Es wird ein Rechteck uebergeben, dass die Positionierung der 
// UIElemente beeinflusst. 
// Es gibt folgende Modi:
// TOPDOWN
// DOWNTOP
// LEFTRIGHT
// RIGHTLEFT
// Es gibt eine primaere und eine sekundaere Anordnung,
// ist eine Reihe(oder Spalte) voll, wird die naechste genutzt
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILAYOUTER_H__7B3C5331_C5DF_47F9_B668_3B299909C87B__INCLUDED_)
#define AFX_UILAYOUTER_H__7B3C5331_C5DF_47F9_B668_3B299909C87B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\UTILS\Rect.h"	// Hinzugefügt von der Klassenansicht
#include "..\ALL2D\ALL2D_BASE\xContainer.h"
#include "..\ALL2D\ALL2D_SPRITES\UISprite.h"

#define LAYOUT_LEFT_RIGHT	0x0001
#define LAYOUT_RIGHT_LEFT	0x0002
#define LAYOUT_UP_DOWN		0x0003
#define LAYOUT_DOWN_UP		0x0004

class UILayouter : public xContainer  
{
public:
	void setBackground(UISprite& addi);
	virtual bool paint(Image& imgBackBuffer);
	UIElement* getElement(string strName);
	int add(UIElement&comp, int insertAt);
	int add(UIElement& comp, bool insertAtEnd=true);			// Gives back the Handle of the added xModule
	void remove(UIElement& component);							//This will be removed by Components Name
	void remove(int compHandle);							//This will be removed by Components Handle
	void layout();
	void setLayoutMode(int Primary, int Secondary=-1);
	void setBorders(int horizontal=0, int vertical=0);
	void setPosition(Rect rctPos);
	UILayouter();
	virtual ~UILayouter();
private:
	Rect rctLayoutPosition;
	int iPrimaryMode,iSecondaryMode;
	int iHorizontalBorder, iVerticalBorder;
	UISprite sprtBackGround;

};

#endif // !defined(AFX_UILAYOUTER_H__7B3C5331_C5DF_47F9_B668_3B299909C87B__INCLUDED_)

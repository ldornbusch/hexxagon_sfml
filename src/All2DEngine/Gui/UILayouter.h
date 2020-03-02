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

#pragma once

#include "../Utils/Rect.h"	// Hinzugefügt von der Klassenansicht
#include "../All2D/All2D_Base/xContainer.h"
#include "../All2D/All2D_Sprites/UISprite.h"
#include "../All2D/All2D_Base/ImageText.h"

//TODO: create enum here
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
	int add(UIElement&comp, unsigned int insertAt);
	int add(UIElement& comp, bool insertAtEnd=true);			// Gives back the Handle of the added xModule
	void remove(UIElement& component);							//This will be removed by Components Name
	void remove(unsigned int compHandle);							//This will be removed by Components Handle
	void layout();
	void setLayoutMode(int Primary, int Secondary=-1);
	void setBorders(int horizontal=0, int vertical=0);
	void setPosition(Rect rctPos);
	static vector<string> formatText(const string text, const unsigned int display_width, const ImageText& font, const char separator=' '); // returns the number of lines which are needed to fit text into the display_width
	static vector<string> splitString(const string text, const char separator=' ');
	UILayouter();
	virtual ~UILayouter();
private:
	Rect rctLayoutPosition;
	int iPrimaryMode,iSecondaryMode;
	int iHorizontalBorder, iVerticalBorder;
	UISprite sprtBackGround;

};

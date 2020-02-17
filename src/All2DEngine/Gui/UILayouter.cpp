// UILayouter.cpp: Implementierung der Klasse UILayouter.
//
//////////////////////////////////////////////////////////////////////

#include "UILayouter.h"
#include <sstream>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UILayouter::UILayouter():xContainer("Layouter")
{
	setLayoutMode(LAYOUT_LEFT_RIGHT);
	setBorders();
}

UILayouter::~UILayouter()
{

}
int UILayouter::add(UIElement&comp, unsigned int insertAt)
{
	return xContainer::add(comp, insertAt);
}
int UILayouter::add(UIElement& comp, bool insertAtEnd)
{
	return xContainer::add(comp, insertAtEnd);
}
void UILayouter::remove(UIElement& component)
{
	xContainer::remove(component);
}
void UILayouter::remove(unsigned int compHandle)
{
	xContainer::remove(compHandle);
}
void UILayouter::layout()
{
	int xco=0,yco=0;	//Coordinaten
	int xpri=0,ypri=0;	// Primary Offsets
	int xsec=0,ysec=0;	// sekundary offsets
	switch(iPrimaryMode){
		case LAYOUT_LEFT_RIGHT:
			xco=0;yco=0;
			xpri=+1;ypri=0;
			break;
		case LAYOUT_RIGHT_LEFT:
			xco=rctLayoutPosition.x2;yco=0;
			xpri=-1;ypri=0;
			break;
		case LAYOUT_UP_DOWN:
			xco=0;yco=0;
			xpri=0;ypri=+1;
			break;
		case LAYOUT_DOWN_UP:
			xco=0;yco=rctLayoutPosition.y2;
			xpri=0;ypri=-1;
			break;
	}
	switch(iSecondaryMode){
		case LAYOUT_LEFT_RIGHT:
			xco=0;
			xsec=+1;ysec=0;
			break;
		case LAYOUT_RIGHT_LEFT:
			xco=rctLayoutPosition.x2;
			xsec=-1;ysec=0;
			break;
		case LAYOUT_UP_DOWN:
			yco=0;
			xsec=0;ysec=1;
			break;
		case LAYOUT_DOWN_UP:
			yco=rctLayoutPosition.y2;
			xsec=0;ysec=-1;
			break;
	}

	for (unsigned int x=0;x<modules.size();x++)
	{
		UIElement* UIObj=(UIElement*)modules[x];
		Rect rctPos=UIObj->getPosition();
		if ((rctPos.y1==RECT_INVALID && rctPos.x1==RECT_INVALID) ||
			(rctPos.y1==0 && rctPos.x1==0))
		{
			UIObj->setPosition( rctLayoutPosition.x1+xco,
								rctLayoutPosition.y1+yco);
			xco+=(xpri*UIObj->getPosition().x2);	// Breite des Obj addieren
			yco+=(ypri*UIObj->getPosition().y2);	// Hoehe des Obj addieren
		}
		if (xco>rctLayoutPosition.x2)	// Wenn breite ueberscritten wird..
		{
			xco=0;
			yco+=(ysec*UIObj->getPosition().y2);
		}
		if (xco<0)	// Wenn breite unterscritten wird..(von rechts kommend)
		{
			xco=rctLayoutPosition.x2;
			yco+=(ysec*UIObj->getPosition().y2);
		}
		if (yco>rctLayoutPosition.y2)	// Wenn breite ueberscritten wird..
		{
			xco+=(xsec*UIObj->getPosition().x2);;
			yco=0;
		}
		if (yco<0)	// Wenn breite unterscritten wird..(von rechts kommend)
		{
			yco=rctLayoutPosition.y2;
			xco+=(xsec*UIObj->getPosition().x2);
		}
	}
}
void UILayouter::setLayoutMode(int Primary, int Secondary)
{
	iPrimaryMode=Primary;
	if (Secondary!=-1)
		iSecondaryMode=Secondary;
	else
		iSecondaryMode=(iPrimaryMode==LAYOUT_LEFT_RIGHT || iPrimaryMode==LAYOUT_RIGHT_LEFT)?
							LAYOUT_UP_DOWN:LAYOUT_LEFT_RIGHT;
}
void UILayouter::setBorders(int horizontal, int vertical)
{
	iHorizontalBorder=horizontal;
	iVerticalBorder=vertical;
}
void UILayouter::setPosition(Rect rctPos)
{
	rctLayoutPosition=rctPos;
}

UIElement* UILayouter::getElement(string strName)
{
	UIElement* retVal=NULL;
	for (unsigned int x=0;x<xContainer::modules.size();x++)
	{
		if (xContainer::modules[x]->getName()==strName)
		{
			retVal=(UIElement*)xContainer::modules[x];
			break;
		}
	}
	return retVal;
}

bool UILayouter::paint(Image &imgBackBuffer)
{
	sprtBackGround.show(imgBackBuffer);
	return 	xContainer::paint(imgBackBuffer);
}

void UILayouter::setBackground(UISprite &addi)
{
	sprtBackGround=addi;
}

vector<string> UILayouter::formatText(const string text, const unsigned int display_width, const ImageText& font, const char separator)
{
    auto retVal = vector<string>();
    string current_line="";
    vector<string> words = splitString(text, separator);
    for (string single_word:words){
        unsigned int word_width=single_word.length() * font.getFontWidth();
        // TODO: break longword if it does not fit into a line
        if (current_line.length() * font.getFontWidth() + word_width < display_width){  // add word to current line
            current_line.append(" ");
        }else{  // break line and start another
            retVal.push_back(current_line);
            current_line="";
        }
        current_line.append(single_word);
    }
    retVal.push_back(current_line);
    return retVal;
}
vector<string> UILayouter::splitString(const string text, const char delim)
{
    auto retVal = vector<string>();
    std::stringstream ss(text);
    string token;
    while (std::getline(ss, token, delim)) {
        retVal.push_back(token);
    }
    return retVal;
}

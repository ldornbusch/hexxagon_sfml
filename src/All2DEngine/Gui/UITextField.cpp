// UITextField.cpp: Implementierung der Klasse UITextField.
//
//////////////////////////////////////////////////////////////////////

#include "UITextField.h"
#include "../All2D/All2D_System.h"
#include "../All2D/All2D_Events/MessageManager.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

UITextField::UITextField()
{
	isActive=false;
	setValue(value("",0));
	iSize=10;
	iTabOrder=0;
	TextBuffer=NULL;
	initTextBuffer();
	ActiveBackground	=0x00888888;
	inActiveBackground	=0x00444444;
	CursorColor			=0x00FFFFFF;
	BlinkFreq			=500;
}

UITextField::UITextField(int size, string val)
{
	isActive=false;
	setValue(value(val,0));
	iSize=size;
	iTabOrder=0;
	TextBuffer=NULL;
	initTextBuffer();
	ActiveBackground	=0x00888888;
	inActiveBackground	=0x00444444;
	CursorColor			=0x00FFFFFF;
	BlinkFreq			=500;

}

UITextField::~UITextField()
{

}
string UITextField::getName()
{
	return UISprite::getName();
}

value UITextField::getValue()
{
	return value(actualString,0);
}

void UITextField::setValue(value val)
{
	actualString = val.first;
}

int UITextField::getTabOrder()
{
	return iTabOrder;
}

void UITextField::setTabOrder(int n)
{
	iTabOrder = n;
}

void UITextField::addChar(char a)
{
	if ((actualString.size()<iSize))
		actualString+=a;
}

void UITextField::setActive(bool flag)
{
	isActive=flag;
}

bool UITextField::paint(Image& img)
{
	if (TextBuffer)
	{
		if (isActive){
			((Image*)TextBuffer)->clear(ActiveBackground);
			if (actualString.length()<iSize)
			{
				static unsigned int blinkTimer=0;
				if (All2D_System::getTime()-blinkTimer>BlinkFreq)
				{
					TextBuffer->box(2+actualString.length()*All2D_System::SystemFont.getFontWidth(), 2,
									All2D_System::SystemFont.getFontWidth()-2, All2D_System::SystemFont.getFontHeight()-2,CursorColor,CursorColor);
					if (All2D_System::getTime()-blinkTimer>2*BlinkFreq)
						blinkTimer=All2D_System::getTime();
				}
			}
		}else
			((Image*)TextBuffer)->clear(inActiveBackground);
		// Coordinate für rechtsbuendige Ausgabe
		All2D_System::SystemFont.PrintAt(*TextBuffer, 0, 2,actualString.c_str());
		TextBuffer->setPosition(Position.x1,Position.y1,TextBuffer->getWidth(), TextBuffer->getHeight());
		TextBuffer->show(img,UISprite::iSpriteBltMode);
	}
	return true;
}

void UITextField::setFocus()
{
	setActive(true);
	MessageManager::handleEvent(new Event(MM_GOT_FOCUS,iTabOrder,0));
}

bool UITextField::handleEvent(Event* evt)
{
	bool wasActive = isActive;
	Point p;
	p.x=0;
	p.y=0;
	switch (evt->Type) {
		case MM_LBUTTONDOWN:
			p=All2D_System::extractMouseCoords(evt);
			setActive(isInside(p.x,p.y));
			if (isActive!=wasActive) {
				if (isActive)
					MessageManager::handleEvent(new Event(MM_GOT_FOCUS,iTabOrder,0));
				else
					MessageManager::handleEvent(new Event(MM_LOST_FOCUS,iTabOrder,0));
			}
			break;
		case MM_MOUSEMOVE:
			p=All2D_System::extractMouseCoords (evt);
			break;
		case MM_CHAR:
		case MM_KEYDOWN:
			if (isActive) {
				char a=(char)evt->wData;
                if (evt->wData>=sf::Keyboard::A && evt->wData<=sf::Keyboard::Z){
                    a=((unsigned char)'A')+evt->wData;
                }
                if (evt->wData>=sf::Keyboard::Num0 && evt->wData<=sf::Keyboard::Num9){
                    a=((unsigned char)'0')+evt->wData;
                }
				switch (a) {
					case sf::Keyboard::Escape:
						setActive(false);
						MessageManager::handleEvent(new Event(MM_LOST_FOCUS,iTabOrder,0));
						break;
					case sf::Keyboard::Return:
					case sf::Keyboard::Tab:
						setActive(false);
						MessageManager::handleEvent(new Event(MM_NEXT_FOCUS,iTabOrder,0));
						break;
					case sf::Keyboard::BackSpace:
						actualString = actualString.substr(0, actualString.size()-1);
						break;
					default:
						addChar(a);
						break;
				}
			}
			break;
	}
	return true;
/*
	if (isActive){
	}
*/
}

void UITextField::initTextBuffer()
{
	if (TextBuffer)
		delete TextBuffer;
	TextBuffer=new UISprite(All2D_System::SystemFont.getFontWidth()*iSize+4 ,All2D_System::SystemFont.getFontHeight()+2);
	((Image*)TextBuffer)->clear(0xffffff);
	TextBuffer->setOffset(0,0);
	TextBuffer->setPriority(getPriority());
	setPosition(RECT_INVALID, RECT_INVALID, TextBuffer->getWidth(), TextBuffer->getHeight());
}

void UITextField::setSize(int newSize)
{
	if (newSize>0)
	{
		iSize=newSize;
		initTextBuffer();
	}
}

void UITextField::setPriority(int prio)
{
	if (TextBuffer)
		TextBuffer->setPriority(prio);
	UISprite::setPriority(prio);

}

void UITextField::finish()
{
	if (TextBuffer)
		delete TextBuffer;
	TextBuffer=NULL;
	UIElement::finish();
}


bool UITextField::isInside(int x, int y)
{

	Rect tmp;
	tmp.setPosition(Position.x1, Position.y1, Position.x2 , Position.y2);
	return tmp.isInside(x,y);
}

int UITextField::getWidth()
{
	if (TextBuffer)
		return TextBuffer->getWidth();
	else
		return RECT_INVALID;
}

int UITextField::getHeight()
{
	if (TextBuffer)
		return TextBuffer->getHeight();
	else
		return RECT_INVALID;
}

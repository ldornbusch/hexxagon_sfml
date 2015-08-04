// UISprite.cpp: Implementierung der Klasse UISprite.
//
//////////////////////////////////////////////////////////////////////

#include "UISprite.h"
#include "../All2D_System.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
bool UISprite::active1=true;	//Als erstes den ersten Buffer benutzen....


UISprite::UISprite() :  BufferPos1(), BufferPos2()
{
	bVisible=true;
	Buffering=false;
	Priority=5;
//	needUpdate=true;
	iSpriteBltMode=IMAGE_BLTMODE_TRANS;
	//Buffer1=new Image();
	//Buffer2=new Image();
}

UISprite::UISprite(int w, int h) : Image(w,h) ,BufferPos1(), BufferPos2()
{
	bVisible=true;
	Buffering=false;
	Priority=5;
	iSpriteBltMode=IMAGE_BLTMODE_TRANS;
//	needUpdate=true;
	//Buffer1=new Image(w,h);
	//Buffer2=new Image(w,h);
}

UISprite::UISprite(Image& clone) :Image(clone),	BufferPos1(), BufferPos2()
{
	bVisible=true;
	Buffering=false;
	Priority=5;
	iSpriteBltMode=IMAGE_BLTMODE_TRANS;
//	needUpdate=true;

	//Buffer1=new Image(clone.getWidth(), clone.getHeight());
	//Buffer2=new Image(clone.getWidth(), clone.getHeight());
}

UISprite::~UISprite()
{

	//delete Buffer1;
	//delete Buffer2;

}

// Clear Sprite from Screen 
void UISprite::clear(Image& Dest)
{
	if (isBuffered())
	{
		// Bei Fullscreen ist DoubleBuffering aktiv.. deswegen muss man immer den 'anderen' Buffer benutzen (den 'vorletzten')
		bool activeBuffer=All2D_System::fullScreen ? !active1: active1 ;
		if (activeBuffer)
		{
			Buffer1->setSrcRect(Rect(0,0,BufferPos1.x2,BufferPos1.y2));
			Buffer1->show(Dest,BufferPos1.x1, BufferPos1.y1, IMAGE_BLTMODE_FAST);
		}else{
			Buffer2->setSrcRect(Rect(0,0,BufferPos2.x2,BufferPos2.y2));
			Buffer2->show(Dest,BufferPos2.x1, BufferPos2.y1, IMAGE_BLTMODE_FAST);
		}
	} 
}

//shows new Sprite.. and buffers the rest
void UISprite::blit(Image& Dest, int bltMode)
{
	if (!bVisible) return;

//  Hier wird gebuffert...Wir muessen die Source clippen!!(ALL3D clippt nur die Destination!!)
	if (isBuffered())
	{
		// Werte aus Dest Retten....
		Rect tmpRect=Dest.getSrcRect();
		Point tmpPoint=Dest.getOffset();
		Dest.setOffset(0,0);

		if (active1)
		{
			BufferPos1=Position;				// richtig bewegen
			BufferPos1.x1-=getOffset().x;
			BufferPos1.y1-=getOffset().y;

			tmpRect.clip(BufferPos1);		// BufferPos and den Rändern clippen
			Dest.setSrcRect(BufferPos1);
			Dest.show(*Buffer1,0,0, IMAGE_BLTMODE_FAST);
		}else{
			BufferPos2=Position;				// richtig bewegen
			BufferPos2.x1-=getOffset().x;
			BufferPos2.y1-=getOffset().y;

			tmpRect.clip(BufferPos2);		// BufferPos and den Rändern clippen
			Dest.setSrcRect(BufferPos2);
			Dest.show(*Buffer2,0,0, IMAGE_BLTMODE_FAST);
		}
		// Werte resturieren...
		Dest.setSrcRect(tmpRect);
		Dest.setOffset(tmpPoint.x, tmpPoint.y);	
	}
	if (Position.x2==Image::getSrcRect().x2 && Position.y2==Image::getSrcRect().y2)	// evl. stretchen, bzw. spiegeln
		Image::show(Dest,Position.x1,Position.y1,bltMode);
	else
		Image::show(Dest,Position.x1,Position.y1,Position.x2,Position.y2, bltMode);
}

// registers Sprite
void UISprite::show(Image& Dest,int bltMode)
{
	if (bVisible)
	{
		if (bltMode==0)
			bltMode=iSpriteBltMode;
		SpriteEntry* tmpEntry= new SpriteEntry(this,Priority,bltMode);
		All2D_System::spriteManager.add(tmpEntry);
	}
	
/*		
		
//		needUpdate=false;
*/
}

bool UISprite::isInside(int x, int y)
{
//	if (offset.x==0 && offset.y==0)
//		return Position.isInside(x,y);

	Rect tmp;
	tmp.setPosition(Position.x1-offset.x, Position.y1-offset.y, 
					Position.x2 , Position.y2);
	return tmp.isInside(x,y);
}

bool UISprite::paint(Image& backBuffer)
{
	if (bVisible) 
		show(backBuffer, iSpriteBltMode);
	return true;
}

void UISprite::setPriority(int i)
{
	Priority=i;
}
int  UISprite::getPriority()
{	return Priority;}

/*void UISprite::setPosition(int x1, int y1, int w, int h)
{
	UIElement::setPosition(x1,y1,w,h);
//	needUpdate=true;
}
*/
bool UISprite::loadImage(string n)
{
	bool retVal=false;
	retVal=Image::loadImage(All2D_System::dataPath(n));
/*	
	Buffer1->resize(getWidth(), getHeight());
	Buffer2->resize(getWidth(), getHeight());
	Buffer1->setOffset(0,0);
	Buffer2->setOffset(0,0);
*/
	setPosition(RECT_INVALID,RECT_INVALID,getWidth(), getHeight());
	return retVal;
}

void UISprite::setOffset(int x, int y)
{
	Image::setOffset(x,y);
}


void UISprite::setBuffered(bool flag)
{
	Buffering=flag;
}

bool UISprite::isBuffered()
{
	return Buffering;
}

void UISprite::finish()
{
	Buffering=false;
	Priority=5;
//	needUpdate=true;

	if (Buffering)
	{
		Buffer1->finish();
		Buffer2->finish();
	}

	Image::finish();
	UIElement::finish();
}

void UISprite::setVisible(bool visible)
{
	bVisible = visible;
}

bool UISprite::isVisible()
{
	return bVisible;
}

void UISprite::resize(int w, int h)
{
	Image::resize(w,h);
	setPosition(Position.x1,Position.y1,w,h);	//aktuelle Groesse Update
}

void UISprite::cloneImage(Image& clone)
{
	Image::cloneImage(clone);
	setPosition(RECT_INVALID, RECT_INVALID,getWidth(), getHeight());
}

void UISprite::setBlitMode(int bltMode)
{
	iSpriteBltMode=bltMode;
}

// UISprite.h: Schnittstelle für die Klasse UISprite.
// Ein Sprite ist ein Image mit einer festen Position am Bildschirm
// Ein Sprite hat zusätzlich einen Backbuffer, der den
// Hintergrund  Sprites rettet					(implemented on 30.04.2001).
// Ein Sprite kann mit anderen Sprites kollidieren 	(implemented on xx.xx.xxxx).
//////////////////////////////////////////////////////////////////////

#pragma once

#include "UIElement.h"
#include "../All2D_Base/Image.h"
#include "../../Utils/Rect.h"	// Hinzugefügt von der Klassenansicht


class UISprite :
	public virtual Image  ,
	public virtual UIElement
{
public:
	void setBlitMode(int bltMode);
	virtual void cloneImage(Image& clone);
	void resize(int w, int h);
	virtual bool isVisible();
	virtual void setVisible(bool visible);
	virtual void finish();
	bool isBuffered();
	void setBuffered(bool flag);
	virtual void setOffset(int x, int y);
	virtual bool loadImage(string n);
	virtual void setPriority(int i);
	virtual int  getPriority();
	virtual bool paint(Image& backBuffer);
	virtual bool isInside(int x, int y);
	virtual void clear(Image& Dest);
	virtual void blit(Image& Dest, int bltMode);
	virtual void show(Image& Dest, int bltMode=0);
	UISprite();
	UISprite(int w, int h);
	UISprite(Image& clone);
	virtual ~UISprite();
	static bool active1;	//true=Buffer1 wird bemalt..false=Buffer2 wird bemalt...
protected:
	bool bVisible;
//	bool needUpdate;
	Rect BufferPos1, BufferPos2;
	Image* Buffer1, *Buffer2; // for doubleBuffering ~:-(
	int Priority;
	bool Buffering;
	int iSpriteBltMode;
};

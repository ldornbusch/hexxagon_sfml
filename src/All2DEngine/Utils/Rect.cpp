// Rect.cpp: Implementierung der Klasse Rect.
// Ein Rect ist immer ein Rechteck mit einem oberen linken punkt 
// und einer breite / Hoehe..
//////////////////////////////////////////////////////////////////////

#include "Rect.h"
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Rect::Rect()
{
	x1=RECT_INVALID;
	y1=RECT_INVALID;
	x2=RECT_INVALID;
	y2=RECT_INVALID;
}

Rect::Rect(int x, int y, int w, int h)
{
	x1=RECT_INVALID;
	y1=RECT_INVALID;
	x2=RECT_INVALID;
	y2=RECT_INVALID;
	setPosition(x,y,w,h);
}

Rect::~Rect()
{

}

void Rect::setPosition(int x, int y, int w, int h)
{
	if (x!=RECT_INVALID)
		x1=x;
	if (y!=RECT_INVALID)
		y1=y;
	if (w!=RECT_INVALID)
		x2=w;
	if (h!=RECT_INVALID)
		y2=h;
}

bool Rect::isInside(int x, int y)
{
	if (x>=x1 && y>=y1 && x<=(x1+abs(x2)) && y<=(y1+abs(y2)))
		return true;
	else
		return false;
}

int Rect::getWidth()
{
	return (x2);
}

int Rect::getHeight()
{
	return (y2);
}

bool Rect::operator==(Rect sec)
{
	if (x1==sec.x1 &&
		y1==sec.y1 &&
		x2==sec.x2 &&
		y2==sec.y2 )
		return true;
	else 
		return false;
}

// returns if Rect is Inside
// Coordiantes were set through Reference
bool Rect::clip(Rect &toClip)
{
	// Negative Coords are only for stretchBlits important...
	if (toClip.x2<0)
		toClip.x2=-toClip.x2;
	if (toClip.y2<0)
		toClip.y2=-toClip.y2;

	int myX1, myX2, myY1, myY2;	// no relative Coordinating .. so everything is translated to ABSOLUTE
	int tcX1, tcX2, tcY1, tcY2;	// my.. is this own Instances Coordinates..tC is toClip..
	myX1=x1;myX2=x1+x2;
	myY1=y1;myY2=y1+y2;

	tcX1=toClip.x1; tcX2=toClip.x1+toClip.x2;
	tcY1=toClip.y1; tcY2=toClip.y1+toClip.y2;

	if(tcX2<myX1 || tcX1>myX2)// is Rect on left or Right side??
		return false;

	if(tcY2<myY1 ||tcY1>myY2)	// is Rect on upper or lower side??
		return false;

	// Horizontal Clipping
	if (tcX1<myX1 && tcX2>myX1)	// is toClip starts outer left side, but reaches in ?
	{
		tcX1=myX1;				// new StartPoint
		if (tcX2>myX2)	// reaches it over the whole rectangle ?
			tcX2=myX2;
	}

	if (tcX1>myX1 && tcX1<myX2)	// toClip starts anywhere in our Rect ?
	{
		if(tcX2>myX2)	// does it reach out of right Screen??
			tcX2=myX2;
	}

//	Vertical Clipping...
	if (tcY1<myY1 && tcY2>myY1)	// is toClip starts outer Upper side, but reaches in ?
	{
		tcY1=myY1;				// new StartPoint
		if (tcY2>myY2)	// reaches it over the whole rectangle ?
			tcY2=myY2;
	}

	if (tcY1>myY1 && tcY1<myY2)	// toClip starts anywhere in our Rect ?
	{
		if(tcY2>myY2)	// does it reach out of lower Screen??
			tcY2=myY2;
	}
	
	// calculate the Clipped Rectangle..
	toClip.x1=tcX1;
	toClip.y1=tcY1;
	toClip.x2=tcX2-tcX1;
	toClip.y2=tcY2-tcY1;
	return true;
}

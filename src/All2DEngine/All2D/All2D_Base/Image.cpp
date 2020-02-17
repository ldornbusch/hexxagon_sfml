// Image.cpp: Implementierung der Klasse Image.
//
//////////////////////////////////////////////////////////////////////

#include "../All2D_System.h"
#include "Image.h"
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

//static Members:

Image::Image(): offset()
{
	offset.x=0;
	offset.y=0;
	BitMap=NULL;
	iTransparentCol=0;
}

Image::Image(int w, int h): offset()
{
	offset.x=w/2;
	offset.y=h/2;
	srcRect.setPosition(0,0,w,h);
	BitMap=new CBitMap(w,h);
	iTransparentCol=0;
}

Image::Image(Image* clone): offset()
{
	offset=clone->getOffset();
	srcRect=clone->getSrcRect();
	cloneImage(*clone);
}

Image::~Image()
{
	finish();
}

bool Image::loadImage(string fileName)
{
	if (BitMap!=NULL)
	{
		delete BitMap;
		BitMap=NULL;
	}

	// get preloaded image from picloader
	BitMap=PicLoader::GetBitmap(fileName);

	// set dimensions if image was returned
	if (BitMap!=NULL)	{
		setSrcRect(Rect(0,0,getWidth(),getHeight()));
		return true;
	}

// 	All2D_System::Debug.Printf0("Bild %s nicht gefunden",fileName.c_str());
	return false;
}

void Image::show(Image& destImage, int x, int y, int BltMode)
{
	x-=offset.x;
	y-=offset.y;
	if (BitMap)
	{
		CBitMap*	dest=destImage.getBitMap();
		if (!BitMap->getBitmap())
		{
//			All2D_System::Debug.Printf0("NullPointerBlit!!!");
			return;
		}
		if (dest)
		{
			switch (BltMode)
			{
				case IMAGE_BLTMODE_TRANS:
					BitMap->Blt(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y, iTransparentCol);
					break;
				case IMAGE_BLTMODE_ADD:
					BitMap->BltAdd(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y, iTransparentCol);
					break;
				case IMAGE_BLTMODE_SUB:
					BitMap->BltSub(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y, iTransparentCol);
					break;
				case IMAGE_BLTMODE_FAST:
					BitMap->BltFast(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y);
					break;
				case IMAGE_BLTMODE_HALF:
					BitMap->BltHalfTrans(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y, iTransparentCol);
					break;
				default:
					break;
			}
		}
	}
}
// with stretching....
void Image::show(Image& destImage, int x, int y, int w, int h, int BltMode)
{
	x-=offset.x;
	y-=offset.y;
	if (BitMap)
	{
		CBitMap*	dest=destImage.getBitMap();
		if (dest)
		{
			switch (BltMode)
			{
				case IMAGE_BLTMODE_TRANS:
					BitMap->Blt(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y,w,h, iTransparentCol);
					break;
				case IMAGE_BLTMODE_ADD:
					BitMap->BltAdd(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y,w,h, iTransparentCol);
					break;
				case IMAGE_BLTMODE_SUB:
					BitMap->BltSub(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y,w,h, iTransparentCol);
					break;
				case IMAGE_BLTMODE_HALF:
					BitMap->BltHalfTrans(srcRect.x1,srcRect.y1,srcRect.getWidth(),srcRect.getHeight(),dest, x,y,w,h, iTransparentCol);
					break;
				default:
					break;
			}
		}
	}
}

CBitMap* Image::getBitMap()
{
	return BitMap;
}

void Image::setBitMap(CBitMap *src)
{
	BitMap = src;
	if (BitMap!=NULL)
		setSrcRect(Rect(0,0,BitMap->getWidth(), BitMap->getHeight()));
}

void Image::setOffset(int x, int y)
{
	offset.x=x;
	offset.y=y;
}

Point Image::getOffset()
{
	return offset;
}

int Image::getWidth()
{
if (BitMap)
		return BitMap->getWidth();
	else
		return RECT_INVALID;
}

int Image::getHeight()
{
	if (BitMap)
		return BitMap->getHeight();
	else
		return RECT_INVALID;
}

void Image::setSrcRect(Rect tmp)
{
	srcRect.setPosition(tmp.x1,tmp.y1,tmp.x2,tmp.y2);
}

Rect Image::getSrcRect()
{
	return srcRect;
}

void Image::clear(int Color)
{
	if (BitMap)
		BitMap->Clear(Color);
}

void Image::resize(int newWidth, int newHeight)
{
	if (BitMap)
		delete BitMap;
	BitMap=new CBitMap(newWidth, newHeight);
	setSrcRect(Rect(0,0,newWidth, newHeight));
}

void Image::finish()
{
	unload();
}

void Image::unload()
{
	if (BitMap)
		delete BitMap;

	BitMap=NULL;
}

void Image::cloneImage(Image& srcImage, Rect cloneRect)
{
	if(this!=&srcImage)
	{
		Image::finish();

		CBitMap* clone=srcImage.getBitMap();

		if (clone)
		{
			BitMap = clone->Clone(cloneRect.x1, cloneRect.y1, cloneRect.x2,cloneRect.y2);
			setSrcRect(Rect(0,0,BitMap->getWidth(), BitMap->getHeight()));
		}
		setTransparentColor(srcImage.getTransparentColor());
	}
}

void Image::cloneImage(Image& srcImage)
{
	if(this!=&srcImage)
	{
		Image::finish();

		CBitMap* clone=srcImage.getBitMap();

		setSrcRect(srcImage.getSrcRect());

		if (clone)
		{
			//BitMap = clone->Clone(0, 0, clone->getWidth(),clone->getHeight());
			BitMap = clone->Clone(getSrcRect().x1,getSrcRect().y1 , getSrcRect().getWidth() ,srcRect.getHeight());
			setSrcRect(Rect(0,0,BitMap->getWidth(), BitMap->getHeight()));
		}
		setOffset(srcImage.getOffset().x,srcImage.getOffset().y);
		setTransparentColor(srcImage.getTransparentColor());
	}
}

void Image::line(int x0, int y0, int x1, int y1, int COL)
{
	BitMap->Line(x0,y0,x1,y1,COL);
}

void Image::box(int x0, int y0, int b, int h, int COL)
{
	BitMap->Line(x0,y0,x0,y0+h,COL);
	BitMap->Line(x0,y0+h,x0+b,y0+h,COL);
	BitMap->Line(x0+b,y0+h,x0+b,y0,COL);
	BitMap->Line(x0+b,y0,x0,y0,COL);
}

void Image::box(int x0, int y0, int b, int h, int COL, int FILL)
{

	// normalise offsets
	int iy0=y0, iy1=y0+h;

	// fill inner box
	// skipping first and last line
	for (;++iy0<iy1;) {
		BitMap->Line(x0,iy0,x0+b,iy0,FILL);
	}

	// call box for the frame
	box(x0,y0,b,h,COL);

}

void Image::txtMap(Image& destination, Point *vertex, int n)
{
	CBitMap* dest=destination.getBitMap();
	CBitMap* src=getBitMap();
	if (dest && src)
		dest->PolyTxT(vertex,n, src);
}


int Image::getTransparentColor()
{
	return iTransparentCol;
}

void Image::setTransparentColor(int col)
{
	iTransparentCol=col;
}

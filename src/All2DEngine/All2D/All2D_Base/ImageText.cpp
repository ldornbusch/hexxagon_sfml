// ImageText.cpp: Implementierung der Klasse ImageText.
//
//////////////////////////////////////////////////////////////////////

#include "../All2D_System.h"
#include "ImageText.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ImageText::ImageText()
{
}

ImageText::~ImageText()
{

}

bool ImageText::loadFont(string fileName)
{
	return loadImage(fileName);
}
void ImageText::cloneFont(ImageText& scrFont)
{
	Image::cloneImage(scrFont);
	FontInit(scrFont.getFontWidth(),scrFont.getFontHeight(),scrFont.getCharPerRow(), scrFont.getTranslationTable());
}
void ImageText::FontInit(int charWidth, int charHeight, int charPerRow, const char *translationTable)
{
	setFontWidth(charWidth);
	setFontHeight(charHeight);
	setCharPerRow(charPerRow);
	setTranslationTable(translationTable);
}

void ImageText::PrintAt(Image& BackBuffer, int x, int y, const char *text, int bltMode, int length,int xStretch,int yStretch)
{
	switch (bltMode)
	{
	case IMAGE_BLTMODE_TRANS:
		WriteString(BackBuffer, x,y,(char*)text, IMAGE_BLTMODE_TRANS, length, xStretch, yStretch);
	break;
	case IMAGE_BLTMODE_ADD:
		WriteString(BackBuffer, x,y,(char*)text, IMAGE_BLTMODE_ADD, length, xStretch, yStretch);
	break;
	case IMAGE_BLTMODE_SUB:
		WriteString(BackBuffer, x,y,(char*)text, IMAGE_BLTMODE_SUB, length, xStretch, yStretch);
	break;
	case IMAGE_BLTMODE_FAST:
		WriteString(BackBuffer, x,y,(char*)text, IMAGE_BLTMODE_FAST, length, xStretch, yStretch);
	break;
	case IMAGE_BLTMODE_HALF:
		WriteString(BackBuffer, x,y,(char*)text, IMAGE_BLTMODE_HALF, length, xStretch, yStretch);
	break;
	}
}

void ImageText::PrintCenter(Image& BackBuffer, int y, const char *text, int bltMode, int length,int xStretch,int yStretch, int xOffset)
{
	int iLen = length;
	if (iLen < 0) iLen = strlen( text );
	int x = (BackBuffer.getWidth() - ((xStretch==0?getFontWidth():xStretch) * iLen)) * 0.5;
	PrintAt( BackBuffer, x+xOffset, y, text, bltMode, iLen+1, xStretch, yStretch );
}

//*********************************************************************
// WriteStringAdd(Destination,x,y, String, length)
// schreibt einen String an x.y in additiver Transparenz..
void ImageText::WriteString(Image& Dest,int x, int y, char *String,int bltMode, int len,int xStretch,int yStretch)
{
	int iCharWidth=(xStretch==0)?FontWidth:xStretch;
	char l;
	int xco,yco;
	int letter=0;
	if (len<0)	len=32000;
	xco=x;
	yco=y;
	l=String[letter++];
	while ((l!=0)&&(letter<len))
	{
		if (xco<Dest.getWidth())
			if (WriteChar(Dest, xco,yco,l, bltMode,xStretch, yStretch))
				xco+=iCharWidth;
		l=String[letter++];
	}
}


// WriteScatter(Destination ,x,y,String, Scatter Factor,Length)
// Schreibt einen Text verwackelt und additiv.. scatter Factor gibt die Verwackelung in Pixeln an..
void ImageText::WriteScatter(Image& Dest, int x, int y, char *String, int scatter, int bltMode, int Len)
{
	x=x+rand()%scatter-(scatter>>1);
	y=y+rand()%scatter-(scatter>>1);
	WriteString(Dest,x,y,String,bltMode,Len);
}

// private..Schreibt ein einzelnes Zeichen..
bool ImageText::WriteChar(Image& Dest, int x, int y, char strChar, int bltMode, int xStretch,int yStretch)
{
	int xle=0;
	int yle=0;
	int index=0;
	index=findChar(strChar);

	if (index<0)
		return false;
	yle=(int)(index/CharPerRow)*FontHeight;
	xle= (index-((yle /FontHeight) * CharPerRow))*FontWidth;
	setSrcRect(Rect(xle,yle,FontWidth, FontHeight));
	if (xStretch==0 && yStretch==0)
		show(Dest,x,y,bltMode);
	else
		show(Dest,x,y,xStretch,yStretch, bltMode);
	return true;
}

int ImageText::findChar(char c2Find)
{
	int retVal=0;
	while ((TranslationTable[retVal]!=c2Find)
			&&TranslationTable[retVal]!=0)
		retVal++;
	if (TranslationTable[retVal]!=0)
		return retVal;
	else
		return -1;
}

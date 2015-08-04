// ImageText.h: Schnittstelle f�r die Klasse ImageText.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGETEXT_H__EC7BC929_C165_40C1_AC5D_9AEBE8F054F8__INCLUDED_)
#define AFX_IMAGETEXT_H__EC7BC929_C165_40C1_AC5D_9AEBE8F054F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Image.h" // Hinzugef�gt von der Klassenansicht

#include <string>
using namespace std;

class ImageText :  public Image
{
public:
	int findChar(char c2Find);
	void PrintCenter(Image& BackBuffer, int y, const char* text, int bltMode=IMAGE_BLTMODE_TRANS, int length=-1,int xStretch=0,int yStretch=0,int xOffset=0);
	void PrintAt(Image& BackBuffer, int x, int y, const char* text, int bltMode=IMAGE_BLTMODE_TRANS,int length=-1,int xStretch=0,int yStretch=0);
	void FontInit(int charWidth=24, int charHeight=24,int charPerRow=20, char* translationTable=" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]�_'abcdefghijklmnopqrstuvwxyz{|}������");
	ImageText();
	virtual ~ImageText();

	bool loadFont(string fileName);

	void cloneFont(ImageText& srcImage);

//Inline Interface GET/SET - Routinen
	int getPixPerCharRow()			{ return PixPerCharRow;			}
	int getCharPerRow()				{ return CharPerRow;				}
	char* getTranslationTable()	{ return TranslationTable;	}
	int getFontHeight()				{ return FontHeight;				}
	int getFontWidth()					{ return FontWidth;					}
	int getTextMode()					{ return TextMode;					}
	void setPixPerCharRow(int iParam)		{ PixPerCharRow=iParam;		}
	void setCharPerRow(int iParam)			{ CharPerRow=iParam;			}
	void setTranslationTable(char* iParam){ TranslationTable=iParam;}
	void setFontHeight(int iParam)			{ FontHeight=iParam;			}
	void setFontWidth(int iParam)				{ FontWidth=iParam;				}
	void setTextMode(int iParam)				{ TextMode=iParam;				}

	//  Public Methods
	void WriteString(Image& Dest, int x, int y, char* String,int bltMode=IMAGE_BLTMODE_TRANS, int len=-1,int xStretch=0,int yStretch=0);
	void WriteScatter(Image& Dest, int x, int y, char* String, int scatter=3, int bltMode=IMAGE_BLTMODE_TRANS, int Len=-1);

private:
	bool blnColorReplacementEnabled;
	int PixPerCharRow;			//The Number of Pixels in every CharRow (= CharPerRow*FontWidth*FontHeight)
	int CharPerRow;					//How many Chars in everyRow of the BMap
	char* TranslationTable;	//The TranslationTable to find any Chars
	int FontHeight;					//The Height of Font in Pixels
	int FontWidth;					//The Width of Font in Pixels
	int TextMode;						//The Blitmode: Solid, transp, halfhalf, additional: 0-4
  int TextWidth;

protected:
  bool WriteChar(Image& Dest, int x, int y, char strChar, int bltMode=IMAGE_BLTMODE_TRANS, int xStretch=0,int yStretch=0);
};

#endif // !defined(AFX_IMAGETEXT_H__EC7BC929_C165_40C1_AC5D_9AEBE8F054F8__INCLUDED_)

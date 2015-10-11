// ImageText.h: Schnittstelle für die Klasse ImageText.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "Image.h" // Hinzugefügt von der Klassenansicht

#include <string>
using namespace std;

class ImageText :  public Image
{
public:
	int findChar(char c2Find);
	void PrintCenter(Image& BackBuffer, int y, const char* text, int bltMode=IMAGE_BLTMODE_TRANS, int length=-1,int xStretch=0,int yStretch=0,int xOffset=0);
	void PrintAt(Image& BackBuffer, int x, int y, const char* text, int bltMode=IMAGE_BLTMODE_TRANS,int length=-1,int xStretch=0,int yStretch=0);
	void FontInit(int charWidth=24, int charHeight=24,int charPerRow=20, const char* translationTable=" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]ß_'abcdefghijklmnopqrstuvwxyz{|}ÄäÖöÜü");
	ImageText();
	virtual ~ImageText();

	bool loadFont(string fileName);

	void cloneFont(ImageText& srcImage);

//Inline Interface GET/SET - Routinen
	int getPixPerCharRow()			{ return PixPerCharRow;			}
	int getCharPerRow()				{ return CharPerRow;				}
	const char* getTranslationTable()	{ return TranslationTable;	}
	int getFontHeight()				{ return FontHeight;				}
	int getFontWidth()					{ return FontWidth;					}
	int getTextMode()					{ return TextMode;					}
	void setPixPerCharRow(int iParam)		{ PixPerCharRow=iParam;		}
	void setCharPerRow(int iParam)			{ CharPerRow=iParam;			}
	void setTranslationTable(const char* iParam){ TranslationTable=iParam;}
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
	const char* TranslationTable;	//The TranslationTable to find any Chars
	int FontHeight;					//The Height of Font in Pixels
	int FontWidth;					//The Width of Font in Pixels
	int TextMode;						//The Blitmode: Solid, transp, halfhalf, additional: 0-4
  int TextWidth;

protected:
  bool WriteChar(Image& Dest, int x, int y, char strChar, int bltMode=IMAGE_BLTMODE_TRANS, int xStretch=0,int yStretch=0);
};

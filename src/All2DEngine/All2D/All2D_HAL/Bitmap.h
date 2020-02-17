// BitMap.h: Schnittstelle für die Klasse CBitMap.
// Die Bitmap Klasse kapselt eine 32Bit-Bitmap
// Und stellt Funktionen für Effekte, Clipping,
// Sprites, und mehr zur Verfügung
//////////////////////////////////////////////////////////////////////

#pragma once

//#define BYTE unsigned char
#define _32BPP
#ifdef _32BPP
#define WINPLANES 32	// 32 BIT Bitplane
#else
#define WINPLANES 16	// 16 BIT Bitplane
#endif

#if WINPLANES < 32


	#define PIXEL unsigned short		// Type to store 1 Pixel

	#define PIXELMASK	0xffff			// MASKS ALL visible Colors
	#define HBRITEMASK	0xfbef			// MASKS Half Brite Colors
	#define ADDMASK		0xf7df			// MASKS FOR ADDITIVE BLENDING
	#define ADDOVERMASK	0x10820			// MASKS FOR SUBSTRACT OVERFLOW

	#define ADDMASKSHIFT 0x5			// Number OF SHIFTS TO Substract ADDMASK

	#define RMASK 0xf800				// MASK FOR RED COMPONENT
	#define GMASK 0x07e0				// MASK FOR GREEN COMPONENT
	#define BMASK 0x001f				// MASK FOR BLUE COMPONENT
	#define AMASK 0x0000				// MASK FOR ALPHA COMPONENT (NOT IMPLEMENTED)

	#define DEPTH 16
	#define RSHIFT 8					// NUMBER OF SHIFTS TO GET RED ON PLACE
	#define GSHIFT 3					// NUMBER OF SHIFTS TO GET GREEN ON PLACE
	#define BSHIFT 3					// NUMBER OF SHIFTS TO GET BLUE ON PLACE
	#define ASHIFT 24					// NUMBER OF SHIFTS TO GET ALPHA ON PLACE
	#define SHIFT2BYTES 1				// Anzahl um die man shiften muss, um die Anzahl der Bytes zu erhalten : zB bei 32BIT muss man 2 mal shiften(je Pixel 4 Bytes.)  , bei 16 Bit nur 1 mal shiften (16 Bit = 2 Bytes)

	#define NUMBYTES 2					// Number Of Bytes per Pixel

	#define TRANSPARENCE 0xf81f	// TRANSPARENCE FÜR PNG-LOADING
	#define STDTRANSCOLOR 0x00		// STANDARD FARBE FÜR TRANSPARENCE BEI BLITTEN

#else // WINPLANES < 32

	#define PIXEL unsigned int				// Type to store 1 Pixel

	#define PIXELMASK	0x00ffffff			// MASKS ALL visible Colors
	#define HBRITEMASK	0x007f7f7f			// MASKS Half Brite Colors (erst shiften, dann ausmaskieren...->MSB raus)
	#define ADDMASK		0x00fefeff			// MASKS FOR ADDITIVE BLENDING (LSB raus
	#define ADDOVERMASK	0x01010100			// MASKS FOR SUBSTRACT OVERFLOW (Nur LSB an)

	#define ADDMASKSHIFT 0x8				// Number OF SHIFTS TO Substract ADDMASK

	#define RMASK 0x00ff0000				// MASK FOR RED COMPONENT
	#define GMASK 0x0000ff00				// MASK FOR GREEN COMPONENT
	#define BMASK 0x000000ff				// MASK FOR BLUE COMPONENT
	#define AMASK 0x00000000				// MASK FOR ALPHA COMPONENT (NOT IMPLEMENTED)

	#define DEPTH 32
	#define RSHIFT 16						// NUMBER OF SHIFTS TO GET RED ON PLACE
	#define GSHIFT 8						// NUMBER OF SHIFTS TO GET GREEN ON PLACE
	#define BSHIFT 0						// NUMBER OF SHIFTS TO GET BLUE ON PLACE
	#define ASHIFT 24						// NUMBER OF SHIFTS TO GET ALPHA ON PLACE
	#define SHIFT2BYTES 2					// Anzahl um die man shiften muss, um die Anzahl der Bytes zu erhalten : zB bei 32BIT muss man 2 mal shiften(je Pixel 4 Bytes.)  , bei 16 Bit nur 1 mal shiften (16 Bit = 2 Bytes)

	#define NUMBYTES 4						// Number Of Bytes per Pixel

	#define TRANSPARENCE  0x00ff00ff	// TRANSPARENCE FÜR PNG-LOADING
	#define STDTRANSCOLOR 0x00000000	// STANDARD FARBE FÜR TRANSPARENCE BEI BLITTEN

#endif  //WINPLANES < 32

typedef enum tagIMAGETYPES {
	IMAGETYPE_BMP,
	IMAGETYPE_PCX,
	IMAGETYPE_JPG,
	IMAGETYPE_PNG
} IMAGETYPES;

#include <stdio.h>
#include "../../Utils/Point.h"

#include <SFML/Graphics.hpp>

#include <string>
using std::string;

class CBitMap
{
public:
// SFML wrapper methods
    void returnImage(sf::Image& img);
    void createFromImage(sf::Image& img);

	bool Load(string fileName);
	void LineAdd(int x1, int y1, int x2, int y2, int col1, int col2);
	void Line(int x1, int y1, int x2, int y2, int Col);
	void Line(int x1, int y1, int x2, int y2, int col1, int col2);
    void LensFlare(CBitMap* Src,int LX, int LY, int sizeX=128, int sizeY=128);
    void BlendPixel(CBitMap* Src, CBitMap* Dest, CBitMap* Mask, unsigned int Counter);
	CBitMap* Clone(unsigned int x=0,unsigned  int y=0, int Wid=320, int Hei=320);
	void Blend(CBitMap* Source, CBitMap* Dest, int Alpha);
	void Blt(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, PIXEL transp=0);
	void Blt(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, PIXEL transp=0); // BltStretch
	void BltAdd(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int Shift=0);
	void BltAdd(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, int Shift=0); // BltStretch
	void BltSub(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int Shift=0);
	void BltSub(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, int Shift=0); // BltStretch
	void BltTV(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest,int verzehr, PIXEL transp=0);
	void BltHalfTrans(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, PIXEL transp=0);
	void BltHalfTrans(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, PIXEL transp=0); // BltStretch
	void BltFast(int Xco, int Yco,int Wid, int Hei, CBitMap*Dest, int XDest, int YDest);
	void BillBoard(int Xco, int Yco,int Wid, int Hei, CBitMap*Dest, int XDest, int YDest, int ZDest,int Shift=-1);

	void InitDeltaMap();
	void InitPhong(int Phong =254, PIXEL Col=PIXELMASK, int Size=256);
	void Bump(CBitMap* Bump, CBitMap* Phong, int LX, int LY);
	void Fluid(CBitMap* Source , CBitMap* FluidMap);

	inline int getPixel(unsigned int x, unsigned int y);
	int getPitch();
	int CalcPixPerRow();		//Calculates the Bytes per Row and sets BytesPerPixel
	inline unsigned int getBytesPerRow(){return ((Pitch+Width)*BytesPerPixel) ;}
	int getHeight(){	return Height; }
	int getWidth() {	return Width ; }
	PIXEL* getBitmap();

	inline float SubPixel(float x);
	void Clear(int Col=0);
	void Dot(unsigned int x, unsigned int y, PIXEL Col);

	void LineTxt(int x1,int y1,int Wid, CBitMap* Source,int xt1,int yt1,int xt2,int yt2);
	void PolyTxT(Point* vertex, int n, CBitMap* Texture);

	void Poly(Point* vertex, int n, PIXEL Col=PIXELMASK);

	void PolyFiller(Point * vertex,int n,PIXEL Col, int RenderMode=0);

	void TextureMapper(Point * vertex,CBitMap * pTexture);

  void Done();
	void Init(PIXEL* ptrBitMap,int W, int H, int D, int Mod);

	void XorPattern();

	CBitMap(unsigned int Width, unsigned int Height);
	CBitMap(const char* imgFile);
	CBitMap();
	virtual ~CBitMap();

private:
	bool bClone;
	inline void DrawRenderMode(int y1, int y2,int RGB, int RM);
	inline void DrawSolidSegment(int y1, int y2,int RGB);
	inline void DrawAlphaSegment(int y1, int y2,int RGB);
	inline void DrawAdditiveSegment(int y1, int y2,int RGB);

	inline void DrawTextureSegment (int y1, int y2,unsigned int * pSource);

	int ABS(int arg);
	unsigned char GetC(FILE *stream);

	unsigned int BytesPerPixel;
	PIXEL* BMap;
	unsigned int Pitch;		//Breite der Bitmap = Pitch + Width
	unsigned int Width;
	unsigned int Height;
	unsigned int Depth;
	char	Palette[1024];	//aarrggbb for Hermes compatibility

protected:
    float Left_dXdY;
    float Right_dXdY;
    float LeftX;
    float RightX;

    float LeftU;
    float LeftV;
    float Left_dUdY;
    float Left_dVdY;
    float dUdY;
    float dVdY;
    float dVdX;
    float dUdX;

    unsigned int * pPolyDest;
};

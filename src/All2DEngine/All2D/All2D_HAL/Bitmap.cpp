// BitMap.cpp: Implementierung der Klasse CBitMap.
//
//////////////////////////////////////////////////////////////////////
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include <SFML/Graphics.hpp>

#include "BitMap.h"

#include "../All2D_System.h"


//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////
CBitMap::CBitMap()	//übergibt ein CBitmap-Object, das noch initialisiert werden muss.
{
	BMap=NULL;
	Height=0;
	Width=0;
	Depth=0;
	Pitch=0;
	CalcPixPerRow();
	bClone=true;
}

CBitMap::~CBitMap()
{
  if ((BMap)&&(!bClone))		//Nur Freigeben, wenn die Bitmap kein Clone ist
	{
		delete BMap;
		BMap=NULL;
	}
}

CBitMap::CBitMap(const char *fileName)
{
  BMap=NULL;
  Height=0;
  Width=0;
	Depth=0;
	Pitch=0;
	Load(fileName);
	CalcPixPerRow();
  bClone=false;
}
/////////////////////////////Laderoutinen/////////////////////////////////
bool CBitMap::Load(string fileName)
{
	bool retVal=false;
	bClone=false; // Wenn ich das Bild geladen habe, dann bin ich nicht geClont
    sf::Image img ;
    img.loadFromFile(fileName);
    createFromImage(img);
	return retVal;
}

void CBitMap::returnImage(sf::Image& img){
    if ((int)img.getSize().x != this->getWidth() || (int)img.getSize().y!=this->getHeight()){
        img.create(this->getWidth(), this->getHeight());
    }
    sf::Uint8* tmp = (sf::Uint8*) img.getPixelsPtr();
	for(unsigned int x=0;x<Width*Height;++x){  // todo: include pitch in calculation
        PIXEL pix=BMap[x];
        BYTE r=(pix & RMASK) >> RSHIFT;
        BYTE g=(pix & GMASK) >> GSHIFT;
        BYTE b=(pix & BMASK) >> BSHIFT;
        BYTE a=255;
        tmp[x*4+0]= r;
        tmp[x*4+1]= g;
        tmp[x*4+2]= b;
        tmp[x*4+3]= a;
	}
}
void CBitMap::createFromImage(sf::Image& img){
    int w=img.getSize().x;
    int h=img.getSize().y;
	Width=w;
	Height=h;
	Depth=DEPTH;
	Pitch=0;
	CalcPixPerRow();
	BMap=new PIXEL[Width * Height];
	const sf::Uint8* tmp = img.getPixelsPtr();
	for(int x=0;x<w*h;++x){
        BYTE r=tmp[x*4+0];
        BYTE g=tmp[x*4+1];
        BYTE b=tmp[x*4+2];
        //BYTE a=tmp[x*4+3];
        BMap[x]= ((r<<RSHIFT)& RMASK) | ((g<<GSHIFT)& GMASK) | ((b>>BSHIFT)& BMASK) ;
	}
}

////////////////////////Leere Bitmap//////////////////////////
CBitMap::CBitMap(unsigned int W, unsigned int H)
{
	BMap=NULL;
	Width=W;
	Height=H;
	Depth=DEPTH;
	Pitch=0;
	CalcPixPerRow();
	BMap=new PIXEL[Width * Height];
	Clear();
	bClone=false;
}

//  ******************************* Methoden Aufrufe ********************************************

//Löscht den Bildschirm Col konnte nur ein Byte sein
void CBitMap::Clear(int Col)
{
	if (BMap)
	{

		int a=(Col & 0xff000000) >> 24 ;
		int r=(Col & 0x00ff0000) >> 16 ;
		int g=(Col & 0x0000ff00) >> 8;
		int b=(Col & 0x000000ff) ;
		PIXEL pixCol=((a<<ASHIFT) & AMASK) | ((r<<RSHIFT)& RMASK) | ((g<<GSHIFT)& GMASK) | ((b>>BSHIFT)& BMASK) ;

//		int  SrcMod;
		PIXEL *ptrBMap;
		ptrBMap=BMap ;
//		SrcMod=Width+Pitch;

		for (int y=Height;y>0;y--)
		{
			for (int x=Width;x>0;x--)
				*ptrBMap++= pixCol;
			ptrBMap+=Pitch;
		}


	// DIES IST DIE ALTE(ETWAS SCHNELLERE METHODE..KONNTE ABER KEINE FARBE FÜLLEN..
/*
		for (int y=Height;y>0;y--)
		{
			memset(ptrBMap,Col, Width<<SHIFT2BYTES);
			ptrBMap+=SrcMod;
		}
	*/
	}
}
int inline CBitMap::ABS(int arg)
{
	if (arg<0 ) arg=-arg;
	return arg;
}


BYTE CBitMap::GetC(FILE* stream)
{
	static INT64 Offset;
	Offset++;
	return getc(stream);
}

PIXEL* CBitMap::getBitmap()
{
	return BMap;
}


void CBitMap::Init(PIXEL *ptrBitMap, int W, int H, int D, int Mod)	//Initialisiert ein bestehendes Bitmap zu einer CBitmap-Klasse (DirectX BackBuffer!)
{
	BMap=ptrBitMap;
	Height=H;
	Width=W;
	Depth=D;
	Pitch=Mod;
	bClone=true;		//Bitmap hat keinen eigenen BMap-Memory
	CalcPixPerRow();
}

void CBitMap::Done()	//Deinitialisiert ein CBitmapObject, ohne die Ressourcen freizugeben (zb. beim Backbuffer)
{											// So kann eine bestehende (system)-Bitmap in ein CBitmap-Object umgewandelt werden und später wieder von diesem gelöst werden
	BMap=NULL;
	Height=0;
	Width=0;
	Depth=0;
	Pitch=0;
	bClone=false;
}
// Erstellt einen neuen Bitmap-Clone, mit derselben Bitmap des Ursprungs-Objects
CBitMap* CBitMap::Clone(unsigned int x, unsigned int y, int Wid, int Hei)
{
	CBitMap*	Back;
	int NewPitch, Offset;
	Back=new CBitMap();

	if (x<0) {Wid+=x;x=0;}
	if (y<0) {Hei+=y;y=0;}
	if (x+Wid>Width) Wid=Width-x;
	if (y+Hei>Height) Hei=Height-y;

	NewPitch=Pitch+(Width-Wid);
	Offset=y*(Width+Pitch)+x;

	Back->Init(BMap+Offset,Wid,Hei,Depth,NewPitch);
	return Back;
}

int CBitMap::getPixel(unsigned int x, unsigned int y)		//VerySlow only for initialisations!!
{
	int Offset;
	while(x<0) x+=Width ;
	while(y<0) y+=Height;
	while(x>=Width) x-=Width ;
	while(y>=Height) y-=Height;
	Offset=y*Width+x;
	return BMap[Offset];
}

void CBitMap::Dot(unsigned int x, unsigned int y, PIXEL Col)										// A simple Dot
{
	int Offset;
	if ((x<Width) && (x>0) && (y<Height) && (y>0))
	{
		Offset=y*Width+x;
		BMap[Offset]=Col;
	}

}

void CBitMap::Poly (Point *vertex, int n, PIXEL Col)			// A simple Polygon
{
//    Line(vertex[0].x ,vertex[0].y ,vertex[1].x ,vertex[1].y ,Col);
//    Line(vertex[1].x ,vertex[1].y  ,vertex[2].x ,vertex[2].y ,Col);
//    Line(vertex[2].x ,vertex[2].y  ,vertex[0].x ,vertex[0].y ,Col);

    PolyFiller(vertex,n,Col);

}

int CBitMap::CalcPixPerRow()
{
	switch (Depth)
		{
		case 4:
			BytesPerPixel = 0	;
			break;
		case 8:
			BytesPerPixel = 1;
			break;
		case 15:
			BytesPerPixel = 2;
			break;
		case 16:
			BytesPerPixel = 2;
			break;
		case 24:
			BytesPerPixel = 3;
			break;
		case 32:
			BytesPerPixel = 4;
			break;
		}
	return BytesPerPixel*(Width+Pitch);
}

int CBitMap::getPitch()
{
	return Pitch ;
}

void CBitMap::InitDeltaMap()		//the Differences in X and Y for Fluid and BumpMapping WORKS ONLY IN 32 BIT!!!
{
	unsigned int x,y;
	int dx,dy,left,right;
	int Offset=0;
	//int Offset2=0;
	PIXEL*	Dest;
	if (Depth==32)
	{
		CBitMap*	temp;
		temp=new CBitMap(Width ,Height); //TempoaryMap as big as this one
		if (temp)
		{
			Dest=temp->getBitmap();
			for(x=0;x<Width;x++)
				for(y=0;y<Height; y++)
				{
					Dest[Offset] = BMap[Offset];
					Offset++;
				}
			Offset =0;
			for ( y=0;y<Height; y++)
 				for( x=0;x<Width;x++)
				{
					left	= (short)((temp->getPixel(x-1,y))&0xff);
					right	= (short)((temp->getPixel(x+1,y))&0xff);
					dx=(short)(((left-right)))&0xffff;
					left	= (short)((temp->getPixel(x,y-1))&0xff);
					right	= (short)((temp->getPixel(x,y+1))&0xff);
					dy=(short)(((left-right)))&0xffff;

					BMap[Offset++]=(dy<<16)+dx;
				}
		delete temp;
		}
	}
}

void CBitMap::InitPhong(int Phong, PIXEL Col, int Size )  // WORKS ONLY IN 32 BIT!!
{
	int* ColorMap;
	float intensity;
	int ColorWert;
	int r=(Col&0x00ff0000)>>16;
	int g=(Col&0x0000ff00)>>8;
	int b=(Col&0x000000ff);
	float fr,fg,fb;

	if (BMap) delete BMap;
	Pitch=0;
	BytesPerPixel=4;
	Depth=32;
	Height=Size;
	Width=Size;
	BMap=new PIXEL[Width*Height];

	ColorMap= new int[256];
	for (int i=0;i<Phong;i++)
	{
		fr=(float)r*i/(Phong-1);
		fg=(float)g*i/(Phong-1);
		fb=(float)b*i/(Phong-1);
		ColorMap[i]=((int)(fr)<<16)+((int)(fg)<<8)+((int)(fb));
	}
	for (int i=Phong;i<256;i++)
	{
		ColorMap[i]=Col;
	}

	for (unsigned int y=0;y<Height;y++)
		for (unsigned int x=0;x<Width;x++)
		{
			intensity=1-(((float)x/(Size-1))*((float)x/(Size-1))+((float)y/(Size-1))*((float)y/(Size-1)));
			if (intensity<0) intensity=0;
			ColorWert=(int)(intensity*255);
			BMap[y*Width+x]=ColorMap[ColorWert];
		}
		delete ColorMap;
}

void CBitMap::Fluid(CBitMap *Source, CBitMap *FluidMap)	// WORKS ONLY IN 32 BIT!!
{
	int Offset1=0;
	static int scroll;
	int Offset2=0;
	short dx, dy;
	int srcPixelW, srcW, srcH, FluSize;
	int dummy;
	PIXEL *Flu, *Src, *Dest;
	short *WortBuffer;
	Flu = FluidMap->getBitmap();
	WortBuffer=(short*) Flu;
	FluSize = FluidMap->getHeight() * (FluidMap->getWidth()+FluidMap->getPitch());
	Src =Source->getBitmap();
	Dest=BMap;
	srcPixelW=Source->getWidth()+Source->getPitch();
	srcW=Source->getWidth();
	srcH=Source->getHeight();
	for (unsigned int y=0;y<Height	; y++)
	{
		for(unsigned int x=0;x<Width;x++)
		{
				dummy=(Offset1+scroll);
				if(dummy>=FluSize)
					dummy-=FluSize;
				dummy=dummy<<1;
				dx=ABS(WortBuffer[dummy]) +x;
				dy=ABS(WortBuffer[dummy+1])+y;
				if ((dx)>=srcW) dx-=srcW;
				if ((dy)>=srcH) dy-=srcH;
				Offset2=dy*srcPixelW+dx;			//PerformanceKiller!!
				Dest[Offset1++] = Src[Offset2];
		}
		Offset1+=Pitch;
		Offset2+=Source->getPitch();
	}
	scroll+=FluidMap->getBytesPerRow()-1;
	if (scroll>FluSize) scroll-=FluSize;	//Sonst wird es immer langsamer...
}

void CBitMap::Bump(CBitMap *Bump, CBitMap * Phong, int LX, int LY)	// WORKS ONLY IN 32 BIT!!
{
	int Offset1, Offset2;		//1=Source...2=Bump...3=Phong
	int dx,dy, Size, PixPerRow;
	PIXEL  *ptrDest, *ptrPhong;
	short *ptrBump;
	ptrPhong	= Phong->getBitmap();
	ptrBump		= (short*)Bump->getBitmap();
	Size=Phong->getWidth()-1;
	ptrDest=BMap;
	Offset1=0;
	PixPerRow=Bump->getWidth()+Bump->getPitch();
	for (unsigned int y=0;y<Height; y++)
	{
		for(unsigned int x=0;x<Width;x++)
		{
			dx=ABS(ptrBump[(x+y*PixPerRow)*2]  -x+LX);
			dy=ABS(ptrBump[(x+y*PixPerRow)*2+1]-y+LY);
			if (dx>Size)
				dx=Size;
			if (dy>Size)
				dy=Size;
			Offset2=(dy*(Size+1))+dx;
				ptrDest[Offset1++] = ptrPhong[Offset2];
		}
		Offset1+=Pitch;
		Offset2+=Bump->getPitch();
	}
}

//********************************************************************************************
//*******************************BLITTER METHODEN ANFANG**************************************
//********************************************************************************************
void CBitMap::BillBoard(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int ZDest, int Shift)
{
	if (ZDest>-64)
	{
		int xpro1, ypro1, xpro2,ypro2;	// Die projezierten Coords des BillBoards
		int CenterX, CenterY, Xcoord,Ycoord;
		Xcoord=XDest-(Wid>>1);				//Center finden...
		Ycoord=YDest-(Hei>>1);
		CenterX=Dest->getWidth()>>1;
		CenterY=Dest->getHeight()>>1;
		xpro1= CenterX + ((Xcoord*128)/(ZDest+128));
		ypro1= CenterY + ((Ycoord*128)/(ZDest+128));
		xpro2= CenterX + (((Xcoord+Wid)*128)/(ZDest+128));
		ypro2= CenterY + (((Ycoord+Hei)*128)/(ZDest+128));
		if (Shift>-1)
			BltAdd(Xco,Yco,Wid,Hei,Dest,xpro1,ypro1,xpro2-xpro1,ypro2-ypro1,Shift);
		else
			Blt(Xco,Yco,Wid,Hei,Dest,xpro1,ypro1,xpro2-xpro1,ypro2-ypro1);
	}
}

void CBitMap::BltFast(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest)
{
	int SrcOffset, DestOffset, DstMod, SrcMod;
	PIXEL *ptrSrc, *ptrDst;

	//Ausschlusskriterien:
	if(XDest>Dest->getWidth()) // rechts draussen
		return;
	if(YDest>Dest->getHeight()) // unten raus
		return;
	if ((XDest+Wid)<=0)			//	links draussen
		return;
	if ((YDest+Hei)<=0)			//	oben draussen
		return;

	// Zuerst die Seiten Clippen...
    if (XDest+Wid>Dest->getWidth()) Wid=Dest->getWidth()-XDest;     //RECHTS
    if ((XDest<0) &&(XDest+Wid)>0) { Xco-=XDest;Wid+=XDest;XDest=0; }              //LINKS

    if (YDest+Hei>Dest->getHeight()) Hei=Dest->getHeight()-YDest;   //UNTEN
    if ((YDest<0) &&(YDest+Hei)>0) { Yco-=YDest;Hei+=YDest;YDest=0; }              //OBEN

	SrcOffset=(Width+Pitch)*Yco+Xco;
	ptrSrc=BMap + SrcOffset;
	DestOffset=(Dest->getWidth()+Dest->getPitch())*YDest+XDest;
	ptrDst=Dest->getBitmap() + DestOffset;
	SrcMod=Width+Pitch;
	DstMod=Dest->getWidth() + Dest->getPitch();


	for (int y=Hei;y>0;y--)
	{
		memcpy(ptrDst,ptrSrc, Wid<<SHIFT2BYTES);
		ptrDst+=DstMod;
		ptrSrc+=SrcMod;
	}
}

void CBitMap::Blt(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, PIXEL transp)
{
	int SrcOffset, DestOffset, DstMod, SrcMod;
	PIXEL *ptrSrc, *ptrDst;
	unsigned int actPix;

		//Ausschlusskriterien:
	if(XDest>Dest->getWidth()) // rechts draussen
		return;
	if(YDest>Dest->getHeight()) // unten raus
		return;
	if ((XDest+Wid)<=0)			//	links draussen
		return;
	if ((YDest+Hei)<=0)			//	oben draussen
		return;

	// Zuerst die Seiten Clippen...
    if (XDest+Wid>Dest->getWidth()) Wid=Dest->getWidth()-XDest;     //RECHTS
    if ((XDest<0) &&(XDest+Wid)>0) { Xco-=XDest;Wid+=XDest;XDest=0; }              //LINKS

    if (YDest+Hei>Dest->getHeight()) Hei=Dest->getHeight()-YDest;   //UNTEN
    if ((YDest<0) &&(YDest+Hei)>0) { Yco-=YDest;Hei+=YDest;YDest=0; }              //OBEN

	//Clipping done
	SrcOffset=(Width+Pitch)*Yco+Xco;
	ptrSrc=BMap;
	SrcMod=Width+Pitch-Wid;
	DestOffset=(Dest->getWidth()+Dest->getPitch())*YDest+XDest;
	ptrDst=Dest->getBitmap();
	DstMod=Dest->getWidth() + Dest->getPitch() - Wid;

	for (int y=0;y<Hei;y++)
	{
		for (int x=0;x<Wid;x++)
		{
			actPix=ptrSrc[SrcOffset++];
			if ((actPix&PIXELMASK)==transp)
				DestOffset++;
			else
				ptrDst[DestOffset++]=actPix;
		}
		DestOffset+=DstMod;
		SrcOffset +=SrcMod;
	}
}
void CBitMap::Blt(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, PIXEL transp)
// Very Quick and VERY Dirty converted from Pascal......
{
	int xdir,ydir,xp,yp,xpo,xi,yi;
	int xl,yl;
	int xsc,ysc;
	int SrcWid=Width+Pitch;
	int DstWid=Dest->getWidth() + Dest->getPitch();
	PIXEL* SrcBMap=BMap;
	PIXEL* DstBMap=Dest->getBitmap();
	int SrcPointer, DstPointer;
	if ((XDest+ABS(DestWid)>0) && (XDest<Dest->getWidth() ) &&
      (YDest+ABS(DestHei)>0) && (YDest<Dest->getHeight()))
	{
		if (DestWid==0) DestWid=1;
		if (DestHei==0) DestHei=1;
		if ((XDest<0) && (XDest+ABS(DestWid)>0))               //CLIPPING-AREA....HEADACHE: Stretching+Clipping!...
		{
			xsc=(-XDest*Wid) / ABS(DestWid) ;		// neuer SourceBitmap Start
			if (DestWid<0)
			{
//				Xco=0;				//Xco ist auf jedenfall 0, da die Linke Seite der SRC Bitmap geflippt wird(destWid<0) und deswegen immer am inken Bildrand reinschaut...
				Wid-=xsc;			// Breite wird um factorisierte Pixel kleiner
				DestWid-=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			} else {
				Xco+=xsc;
				Wid-=xsc;
				DestWid+=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			}
			XDest=0;
		}
		if ((XDest<Dest->getWidth()) && (XDest+ABS(DestWid)>Dest->getWidth()))
		{
			xsc=Dest->getWidth()-XDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestWid<0)
			{
				Xco=Wid-xsc;							// Beim geflippten Bild fängt Blitting von hinten an
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=-xsc;
			} else {
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=xsc;
			}
		}
		if ((YDest<0) && (YDest+ABS(DestHei)>0))
		{
			ysc=(-YDest*Hei) / ABS(DestHei) ;
			if (DestHei<0)
			{
//				Yco=ysc;
				Hei-=ysc;
				DestHei-=YDest;
			} else {
				Yco+=ysc;
				Hei-=ysc;
				DestHei+=YDest;
			}
			YDest=0;
		}
		if ((YDest<Dest->getHeight()) && (YDest+ABS(DestHei)>Dest->getHeight()))
		{
			ysc=Dest->getHeight()-YDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestHei<0)
			{
				Yco=Hei-ysc-1;							// Beim geflippten Bild fängt Blitting von hinten an
				Hei=(ysc*Hei) / ABS(DestHei);
				DestHei=-ysc;
			} else {
				Hei=(ysc*Hei) / ABS(DestHei) ;
				DestHei=ysc;
			}
		}
		// Bei Geflipptem BMap, habe ich xp-=1 genommen, da sonst das erste Pixel HINTER der ersten Zeile angezeigt wird..
		// LDORNBUSCH 18.04.01
		// Bei Geflipptem BMap, habe ich yp-=1 genommen, da sonst das erste Pixel HINTER der ersten Zeile angezeigt wird..
		// LDORNBUSCH 23.05.01
		if (DestWid<0)	{ xdir=-1;xp=Wid-1;DestWid=-DestWid;xpo=Wid;}					//Here is the Flipping Part....
		else			{ xdir= 1;xp=0  ;				  xpo=-Wid;}
		if (DestHei<0)	{ ydir=-SrcWid;yp=Hei-1;DestHei=-DestHei;}
		else			{ ydir= SrcWid;yp=0  ;       }
		xi=DestWid;yi=DestHei;

		SrcPointer=(Yco+yp)*SrcWid+Xco+xp;
		DstPointer=YDest*DstWid+XDest;
		for(yl=DestHei;yl>0;yl--)
		{
		  for (xl=DestWid;xl>0;xl--)
			{
				if ((SrcBMap[SrcPointer]&PIXELMASK)!=transp)
				{
					DstBMap[DstPointer]=SrcBMap[SrcPointer];
				}
				DstPointer++;
				xi-=Wid;
				while (xi<=0)
				{	xi+=DestWid;	SrcPointer+=xdir;}
			}
			SrcPointer+=xpo;
			DstPointer+=DstWid-DestWid;
			xi=DestWid;
			yi-=Hei;
			while (yi<=0)
			{	yi+=DestHei;		SrcPointer+=ydir;}
		}
	}
}
// Halfbrite Transparency best use for shadows..
void CBitMap::BltHalfTrans(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, PIXEL transp)
{
	int SrcOffset, DestOffset, DstMod, SrcMod;
	PIXEL *ptrSrc, *ptrDst;
	unsigned int actPix, DestPix;
	// Zuerst die Seiten Clippen...

	//Ausschlusskriterien:
	if(XDest>Dest->getWidth()) // rechts draussen
		return;
	if(YDest>Dest->getHeight()) // unten raus
		return;
	if ((XDest+Wid)<=0)			//	links draussen
		return;
	if ((YDest+Hei)<=0)			//	oben draussen
		return;

    if (XDest+Wid>Dest->getWidth())
		Wid=Dest->getWidth()-XDest;     //RECHTS
    if ((XDest<0) &&(XDest+Wid)>0)
		{ Xco-=XDest;Wid+=XDest;XDest=0; }              //LINKS

    if (YDest+Hei>Dest->getHeight())
		Hei=Dest->getHeight()-YDest;   //UNTEN
    if ((YDest<0) &&(YDest+Hei)>0)
		{ Yco-=YDest;Hei+=YDest;YDest=0; }              //OBEN


	//Clipping done
	SrcOffset=(Width+Pitch)*Yco+Xco;
	ptrSrc=BMap;
	SrcMod=Width+Pitch-Wid;
	DestOffset=(Dest->getWidth()+Dest->getPitch())*YDest+XDest;
	ptrDst=Dest->getBitmap();
	DstMod=Dest->getWidth() + Dest->getPitch() - Wid;

	for (int y=Hei;y>0;y--)
	{
		for (int x=Wid;x>0;x--)
		{

			actPix=ptrSrc[SrcOffset++];
			if ((actPix & PIXELMASK)!=transp)
			{
				DestPix=ptrDst[DestOffset];
				actPix=((actPix>>1)&HBRITEMASK) + ((DestPix>>1)&HBRITEMASK);
				ptrDst[DestOffset++]=actPix;
			} else {
				DestOffset++;
			}
		}
		DestOffset+=DstMod;
		SrcOffset +=SrcMod;
	}
}
void CBitMap::BltHalfTrans(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, PIXEL transp)
// Very Quick and VERY Dirty converted from Pascal......
{
	int xdir,ydir,xp,yp,xpo,xi,yi;
	int xl,yl;
	int xsc,ysc;
	int SrcWid=Width+Pitch;
	int DstWid=Dest->getWidth() + Dest->getPitch();
	PIXEL* SrcBMap=BMap;
	PIXEL* DstBMap=Dest->getBitmap();
	int SrcPointer, DstPointer;
	unsigned int actPix,DestPix,Pixel;//,over

	if ((XDest+ABS(DestWid)>0) && (XDest<Dest->getWidth() ) &&
      (YDest+ABS(DestHei)>0) && (YDest<Dest->getHeight()))
	{
		if (DestWid==0) DestWid=1;
		if (DestHei==0) DestHei=1;

		if ((XDest<0) && (XDest+ABS(DestWid)>0))               //CLIPPING-AREA....HEADACHE: Stretching+Clipping!...
		{
			xsc=(-XDest*Wid) / ABS(DestWid) ;		// neuer SourceBitmap Start
			if (DestWid<0)
			{
//				Xco=0;				//Xco ist auf jedenfall 0, da die Linke Seite der SRC Bitmap geflippt wird(destWid<0) und deswegen immer am inken Bildrand reinschaut...
				Wid-=xsc;			// Breite wird um factorisierte Pixel kleiner
				DestWid-=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			} else {
				Xco+=xsc;
				Wid-=xsc;
				DestWid+=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			}
			XDest=0;
		}
		if ((XDest<Dest->getWidth()) && (XDest+ABS(DestWid)>Dest->getWidth()))
		{
			xsc=Dest->getWidth()-XDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestWid<0)
			{
				Xco=Wid-xsc;							// Beim geflippten Bild fängt Blitting von hinten an
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=-xsc;
			} else {
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=xsc;
			}
		}
		if ((YDest<0) && (YDest+ABS(DestHei)>0))
		{
			ysc=(-YDest*Hei) / ABS(DestHei) ;
			if (DestHei<0)
			{
//				Yco=ysc;
				Hei-=ysc;
				DestHei-=YDest;
			} else {
				Yco+=ysc;
				Hei-=ysc;
				DestHei+=YDest;
			}
			YDest=0;
		}
		if ((YDest<Dest->getHeight()) && (YDest+ABS(DestHei)>Dest->getHeight()))
		{
			ysc=Dest->getHeight()-YDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestHei<0)
			{
				Yco=Hei-ysc-1;							// Beim geflippten Bild fängt Blitting von hinten an
				Hei=(ysc*Hei) / ABS(DestHei);
				DestHei=-ysc;
			} else {
				Hei=(ysc*Hei) / ABS(DestHei) ;
				DestHei=ysc;
			}
		}

		if (DestWid<0)	{ xdir=-1;xp=Wid-1;DestWid=-DestWid;xpo=Wid;}					//Here is the Flipping Part....
		else			{ xdir= 1;xp=0  ;				  xpo=-Wid;}
		if (DestHei<0)	{ ydir=-SrcWid;yp=Hei;DestHei=-DestHei;}
		else			{ ydir= SrcWid;yp=0  ;       }
		xi=DestWid;yi=DestHei;

		SrcPointer=(Yco+yp)*SrcWid+Xco+xp;
		DstPointer=YDest*DstWid+XDest;
		for(yl=DestHei;yl>0;yl--)
		{
			for (xl=DestWid;xl>0;xl--)
			{
				actPix=SrcBMap[SrcPointer]&PIXELMASK;
				if (actPix!=transp)
				{
					DestPix=DstBMap[DstPointer];
					Pixel= ((actPix>>1)&HBRITEMASK) + ((DestPix>>1)&HBRITEMASK);
					DstBMap[DstPointer]=(PIXEL)Pixel;
				}
				DstPointer++;
				xi-=Wid;
				while (xi<=0)
				{		xi+=DestWid;	SrcPointer+=xdir;		}
			}
			SrcPointer+=xpo;
			DstPointer+=DstWid-DestWid;
			xi=DestWid;
			yi-=Hei;
			while (yi<=0)
			{	yi+=DestHei;			SrcPointer+=ydir;			}
		}
	}
}
void CBitMap::BltSub(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int Shift)
{
	int SrcOffset, DestOffset, DstMod, SrcMod;
	PIXEL *ptrSrc, *ptrDst;
	int actPix, DestPix;
	int over,Pixel;
	//Ausschlusskriterien:
	if(XDest>Dest->getWidth()) // rechts draussen
		return;
	if(YDest>Dest->getHeight()) // unten raus
		return;
	if ((XDest+Wid)<=0)			//	links draussen
		return;
	if ((YDest+Hei)<=0)			//	oben draussen
		return;
	// Zuerst die Seiten Clippen...
	if (XDest+Wid>Dest->getWidth()) Wid=Dest->getWidth()-XDest;		//RECHTS
    if ((XDest<0) &&(XDest+Wid)>=0) { Xco-=XDest;Wid+=XDest;XDest=0; }              //LINKS

    if (YDest+Hei>Dest->getHeight()) Hei=Dest->getHeight()-YDest;   //UNTEN
    if ((YDest<0) &&(YDest+Hei)>=0) { Yco-=YDest;Hei+=YDest;YDest=0; }              //OBEN

    //Clipping done
	SrcOffset=(Width+Pitch)*Yco+Xco;
	ptrSrc=BMap;
	SrcMod=Width+Pitch-Wid;
	DestOffset=(Dest->getWidth()+Dest->getPitch())*YDest+XDest;
	ptrDst=Dest->getBitmap();
	DstMod=Dest->getWidth() + Dest->getPitch() - Wid;

	for (int y=0;y<Hei;y++)
	{
		for (int x=0;x<Wid;x++)
		{

			actPix=ptrSrc[SrcOffset++];
			DestPix=ptrDst[DestOffset];
			if ((actPix & PIXELMASK)>0)
			{
				DestPix= (-DestPix-1);

				Pixel= ((actPix)&ADDMASK) + ((DestPix)&ADDMASK);
				over=Pixel&ADDOVERMASK;
				over=over-(over>>ADDMASKSHIFT);
				actPix=-(Pixel|over);

				ptrDst[DestOffset++]=(PIXEL)actPix;
			}
			else
				DestOffset++;
		}
		DestOffset+=DstMod;
		SrcOffset +=SrcMod;
	}
}

void CBitMap::BltSub(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, int Shift)
// Very Quick and VERY Dirty converted from Pascal......
{
	int xdir,ydir,xp,yp,xpo,xi,yi;
	int xl,yl;
	int xsc,ysc;
	int SrcWid=Width+Pitch;
	int DstWid=Dest->getWidth() + Dest->getPitch();
	PIXEL* SrcBMap=BMap;
	PIXEL* DstBMap=Dest->getBitmap();
	int SrcPointer, DstPointer;
	int actPix,DestPix,over,Pixel;
	int ShiftMask;

	if ((Shift>0)&&(Shift<8))
	{
		ShiftMask=(0x00ff>>Shift)&0x00ff;
		ShiftMask=(ShiftMask<<16) | (ShiftMask<<8) | ShiftMask;
	} else ShiftMask=0x00ffffff;

	if ((XDest+ABS(DestWid)>0) && (XDest<Dest->getWidth() ) &&
      (YDest+ABS(DestHei)>0) && (YDest<Dest->getHeight()))
	{
		if (DestWid==0) DestWid=1;
		if (DestHei==0) DestHei=1;
		if ((XDest<0) && (XDest+ABS(DestWid)>0))               //CLIPPING-AREA....HEADACHE: Stretching+Clipping!...
		{
			xsc=(-XDest*Wid) / ABS(DestWid) ;		// neuer SourceBitmap Start
			if (DestWid<0)
			{
//				Xco=0;				//Xco ist auf jedenfall 0, da die Linke Seite der SRC Bitmap geflippt wird(destWid<0) und deswegen immer am inken Bildrand reinschaut...
				Wid-=xsc;			// Breite wird um factorisierte Pixel kleiner
				DestWid-=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			} else {
				Xco+=xsc;
				Wid-=xsc;
				DestWid+=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			}
			XDest=0;
		}
		if ((XDest<Dest->getWidth()) && (XDest+ABS(DestWid)>Dest->getWidth()))
		{
			xsc=Dest->getWidth()-XDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestWid<0)
			{
				Xco=Wid-xsc;							// Beim geflippten Bild fängt Blitting von hinten an
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=-xsc;
			} else {
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=xsc;
			}
		}
		if ((YDest<0) && (YDest+ABS(DestHei)>0))
		{
			ysc=(-YDest*Hei) / ABS(DestHei) ;
			if (DestHei<0)
			{
//				Yco=ysc;
				Hei-=ysc;
				DestHei-=YDest;
			} else {
				Yco+=ysc;
				Hei-=ysc;
				DestHei+=YDest;
			}
			YDest=0;
		}
		if ((YDest<Dest->getHeight()) && (YDest+ABS(DestHei)>Dest->getHeight()))
		{
			ysc=Dest->getHeight()-YDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestHei<0)
			{
				Yco=Hei-ysc-1;							// Beim geflippten Bild fängt Blitting von hinten an
				Hei=(ysc*Hei) / ABS(DestHei);
				DestHei=-ysc;
			} else {
				Hei=(ysc*Hei) / ABS(DestHei) ;
				DestHei=ysc;
			}
		}
		if (DestWid<0)	{ xdir=-1;xp=Wid-1;DestWid=-DestWid;xpo=Wid;}					//Here is the Flipping Part....
		else						{ xdir= 1;xp=0  ;						      xpo=-Wid;}
		if (DestHei<0)	{ ydir=-SrcWid;yp=Hei;DestHei=-DestHei;}
		else						{ ydir= SrcWid;yp=0  ;       }
		xi=DestWid;yi=DestHei;

		SrcPointer=(Yco+yp)*SrcWid+Xco+xp;
		DstPointer=YDest*DstWid+XDest;
		for(yl=DestHei;yl>0;yl--)
		{
		  for (xl=DestWid;xl>0;xl--)
			{
				actPix=SrcBMap[SrcPointer]&PIXELMASK;
				if (actPix>0)
				{
					DestPix=DstBMap[DstPointer];
					DestPix=(-DestPix)-1;
					Pixel= ((actPix)&ADDMASK) + ((DestPix)&ADDMASK);
					over=Pixel&ADDOVERMASK;
					over=over-(over>>ADDMASKSHIFT);
					actPix=-(Pixel|over);

					DstBMap[DstPointer]=(PIXEL)actPix;
				}
				DstPointer++;
				xi-=Wid;
				while (xi<=0)
				{		xi+=DestWid;	SrcPointer+=xdir;		}
			}
			SrcPointer+=xpo;
			DstPointer+=DstWid-DestWid;
			xi=DestWid;
			yi-=Hei;
			while (yi<=0)
			{	yi+=DestHei;			SrcPointer+=ydir;			}
		}
	}
}


void CBitMap::BltAdd(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int Shift)
{
	int SrcOffset, DestOffset, DstMod, SrcMod;
	PIXEL *ptrSrc, *ptrDst;
	int actPix, DestPix;
	int over,Pixel;
	//Ausschlusskriterien:
	if(XDest>Dest->getWidth()) // rechts draussen
		return;
	if(YDest>Dest->getHeight()) // unten raus
		return;
	if ((XDest+Wid)<=0)			//	links draussen
		return;
	if ((YDest+Hei)<=0)			//	oben draussen
		return;
	// Zuerst die Seiten Clippen...
	if (XDest+Wid>Dest->getWidth()) Wid=Dest->getWidth()-XDest;		//RECHTS
    if ((XDest<0) &&(XDest+Wid)>=0) { Xco-=XDest;Wid+=XDest;XDest=0; }              //LINKS

    if (YDest+Hei>Dest->getHeight()) Hei=Dest->getHeight()-YDest;   //UNTEN
    if ((YDest<0) &&(YDest+Hei)>=0) { Yco-=YDest;Hei+=YDest;YDest=0; }              //OBEN

    //Clipping done
	SrcOffset=(Width+Pitch)*Yco+Xco;
	ptrSrc=BMap;
	SrcMod=Width+Pitch-Wid;
	DestOffset=(Dest->getWidth()+Dest->getPitch())*YDest+XDest;
	ptrDst=Dest->getBitmap();
	DstMod=Dest->getWidth() + Dest->getPitch() - Wid;

	for (int y=0;y<Hei;y++)
	{
		for (int x=0;x<Wid;x++)
		{

			actPix=ptrSrc[SrcOffset++];
			DestPix=ptrDst[DestOffset];
			if ((actPix & PIXELMASK)>0)
			{
				Pixel= ((actPix)&ADDMASK) + ((DestPix)&ADDMASK);
				over=Pixel&ADDOVERMASK;
				over=over-(over>>ADDMASKSHIFT);
				actPix=Pixel|over;
				ptrDst[DestOffset++]=(PIXEL)actPix;
			}
			else
				DestOffset++;
		}
		DestOffset+=DstMod;
		SrcOffset +=SrcMod;
	}
}

void CBitMap::BltAdd(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest, int DestWid, int DestHei, int Shift)
// Very Quick and VERY Dirty converted from Pascal......
{
	int xdir,ydir,xp,yp,xpo,xi,yi;
	int xl,yl;
	int xsc,ysc;
	int SrcWid=Width+Pitch;
	int DstWid=Dest->getWidth() + Dest->getPitch();
	PIXEL* SrcBMap=BMap;
	PIXEL* DstBMap=Dest->getBitmap();
	int SrcPointer, DstPointer;
	int actPix,DestPix,over,Pixel;
	int ShiftMask;

	if ((Shift>0)&&(Shift<8))
	{
		ShiftMask=(0x00ff>>Shift)&0x00ff;
		ShiftMask=(ShiftMask<<16) | (ShiftMask<<8) | ShiftMask;
	} else ShiftMask=0x00ffffff;

	if ((XDest+ABS(DestWid)>0) && (XDest<Dest->getWidth() ) &&
      (YDest+ABS(DestHei)>0) && (YDest<Dest->getHeight()))
	{
		if (DestWid==0) DestWid=1;
		if (DestHei==0) DestHei=1;
		if ((XDest<0) && (XDest+ABS(DestWid)>0))               //CLIPPING-AREA....HEADACHE: Stretching+Clipping!...
		{
			xsc=(-XDest*Wid) / ABS(DestWid) ;		// neuer SourceBitmap Start
			if (DestWid<0)
			{
//				Xco=0;				//Xco ist auf jedenfall 0, da die Linke Seite der SRC Bitmap geflippt wird(destWid<0) und deswegen immer am inken Bildrand reinschaut...
				Wid-=xsc;			// Breite wird um factorisierte Pixel kleiner
				DestWid-=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			} else {
				Xco+=xsc;
				Wid-=xsc;
				DestWid+=XDest;		//XDest ist negativ--->DestWid wird absolut kleiner
			}
			XDest=0;
		}
		if ((XDest<Dest->getWidth()) && (XDest+ABS(DestWid)>Dest->getWidth()))
		{
			xsc=Dest->getWidth()-XDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestWid<0)
			{
				Xco=Wid-xsc;							// Beim geflippten Bild fängt Blitting von hinten an
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=-xsc;
			} else {
				Wid=(xsc*Wid) / ABS(DestWid);
				DestWid=xsc;
			}
		}
		if ((YDest<0) && (YDest+ABS(DestHei)>0))
		{
			ysc=(-YDest*Hei) / ABS(DestHei) ;
			if (DestHei<0)
			{
//				Yco=ysc;
				Hei-=ysc;
				DestHei-=YDest;
			} else {
				Yco+=ysc;
				Hei-=ysc;
				DestHei+=YDest;
			}
			YDest=0;
		}
		if ((YDest<Dest->getHeight()) && (YDest+ABS(DestHei)>Dest->getHeight()))
		{
			ysc=Dest->getHeight()-YDest;		//Anzahl der Pixel die verdeckt werden..
			if (DestHei<0)
			{
				Yco=Hei-ysc-1;							// Beim geflippten Bild fängt Blitting von hinten an
				Hei=(ysc*Hei) / ABS(DestHei);
				DestHei=-ysc;
			} else {
				Hei=(ysc*Hei) / ABS(DestHei) ;
				DestHei=ysc;
			}
		}
		if (DestWid<0)	{ xdir=-1;xp=Wid-1;DestWid=-DestWid;xpo=Wid;}					//Here is the Flipping Part....
		else						{ xdir= 1;xp=0  ;						      xpo=-Wid;}
		if (DestHei<0)	{ ydir=-SrcWid;yp=Hei;DestHei=-DestHei;}
		else						{ ydir= SrcWid;yp=0  ;       }
		xi=DestWid;yi=DestHei;

		SrcPointer=(Yco+yp)*SrcWid+Xco+xp;
		DstPointer=YDest*DstWid+XDest;
		for(yl=DestHei;yl>0;yl--)
		{
		  for (xl=DestWid;xl>0;xl--)
			{
				actPix=SrcBMap[SrcPointer]&PIXELMASK;
				if (actPix>0)
				{
				//	actPix=(actPix>>Shift)& ShiftMask;
					DestPix=DstBMap[DstPointer];
					Pixel= ((actPix)&ADDMASK) + ((DestPix)&ADDMASK);
					over=Pixel&ADDOVERMASK;
					over=over-(over>>ADDMASKSHIFT);
					actPix=Pixel|over;
          DstBMap[DstPointer]=(PIXEL)actPix;
				}
				DstPointer++;
				xi-=Wid;
				while (xi<=0)
				{		xi+=DestWid;	SrcPointer+=xdir;		}
			}
			SrcPointer+=xpo;
			DstPointer+=DstWid-DestWid;
			xi=DestWid;
			yi-=Hei;
			while (yi<=0)
			{	yi+=DestHei;			SrcPointer+=ydir;			}
		}
	}
}
void CBitMap::BltTV(int Xco, int Yco, int Wid, int Hei, CBitMap *Dest, int XDest, int YDest,int verzerr, PIXEL transp)
{
	int SrcOffset, DestOffset, DstMod, SrcMod;
	PIXEL *ptrSrc, *ptrDst;
	PIXEL actPix;
	int distort;
	if (verzerr<1) verzerr=1;
	// Zuerst die Seiten Clippen...
    if (XDest+Wid>Dest->getWidth()) Wid=Dest->getWidth()-XDest;     //RECHTS
    if ((XDest<0) &&(XDest+Wid)>0) { Xco-=XDest;Wid+=XDest;XDest=0; }              //LINKS

    if (YDest+Hei>Dest->getHeight()) Hei=Dest->getHeight()-YDest;   //UNTEN
    if ((YDest<0) &&(YDest+Hei)>0) { Yco-=YDest;Hei+=YDest;YDest=0; }              //OBEN

	//Clipping done
	SrcOffset=(Width+Pitch)*Yco+Xco;
	ptrSrc=BMap;
	SrcMod=Width+Pitch-Wid;
	DestOffset=(Dest->getWidth()+Dest->getPitch())*YDest+XDest;
	ptrDst=Dest->getBitmap();
	DstMod=Dest->getWidth() + Dest->getPitch() - Wid;

	for (int y=0;y<Hei;y+=2)
	{
		distort=rand()%verzerr-(verzerr>>1);		//Verzerrung
		SrcOffset+=distort;

		for (int x=0;x<Wid-distort;x++)
		{
			actPix=ptrSrc[SrcOffset++];
			if ((actPix&PIXELMASK)==transp)
				DestOffset++;
			else
				ptrDst[DestOffset++]=actPix;
		}
		DestOffset+=distort;
		DestOffset+=DstMod;
		SrcOffset +=SrcMod;

		distort=rand()%verzerr-(verzerr>>1);		//Verzerrung
		SrcOffset+=distort;
		for (int x=0;x<Wid-distort;x++)
		{
			actPix=ptrSrc[SrcOffset++];
			if ((actPix&PIXELMASK)==transp)
				DestOffset++;
			else{
				actPix=((actPix>>1)&HBRITEMASK) ;
				ptrDst[DestOffset++]=actPix;
			}
		}
		DestOffset+=distort;
		DestOffset+=DstMod;
		SrcOffset +=SrcMod;
	}
}

//********************************************************************************************
//*******************************BLITTER METHODEN ENDE****************************************
//********************************************************************************************


// Dies ist die PolyFill Routine
void CBitMap::PolyFiller(Point * vertex,int n,PIXEL RGB, int RenderMode)
{
    n=n;  // keine warnings !
    Point * V1 = &vertex[0];
    Point * V2 = &vertex[1];
    Point * V3 = &vertex[2];
    if (V1->y > V2->y)
    {
        Point * MTemp;        //swap (&V1,&V2);
        MTemp = V1;
        V1 = V2;
        V2 = MTemp;
    }
    if (V1->y > V3->y)
    {
        Point * MTemp;        //swap(&V1,&V3);
        MTemp = V1;
        V1 = V3;
        V3 = MTemp;
   }
    if (V2->y > V3->y)
    {
        Point * MTemp;        //swap (&V2,&V3);
        MTemp = V2;
        V2 = V3;
        V3 = MTemp;
    }
    /*  SubPixel Accuarcy der Polygon Ecken */
    int y1i = (int)ceil(V1->y);
    int y2i = (int)ceil(V2->y);
    int y3i = (int)ceil(V3->y);
    if (y1i==y3i)
        return;
    pPolyDest = (unsigned int*)getBitmap() + (y1i*getBytesPerRow()>>2);
    /* Konstanten errechnen ...hier kann noch optimiert werden !!! */
     float V1V3 =(float) V3->y - V1->y;
     float V2V3 =(float) V3->y - V2->y;
     float V1V2 =(float) V2->y - V1->y;

     if (!V1V3)        V1V3 =1;
     if (!V2V3)        V2V3 =1;
     if (!V1V2)        V1V2 =1;

     float dXdY_V1V3=(V3->x - V1->x) / V1V3;
     float dXdY_V2V3=(V3->x - V2->x) / V2V3;
     float dXdY_V1V2=(V2->x - V1->x) / V1V2;
    // Stelle fest ob V2 auf der rechten seite oder links
    bool mid = dXdY_V1V3 < dXdY_V1V2;
    if (!mid)
    {
        // V2 Links
        if (y1i==y2i)
        {
            Left_dXdY  = dXdY_V2V3;
            Right_dXdY = dXdY_V1V3;
            LeftX  = (float)V2->x;
            RightX = (float)V1->x;
            DrawRenderMode(y1i, y3i,RGB, RenderMode);
            return;
        }
        Right_dXdY = dXdY_V1V3;
        if (y1i<y2i)
        {
            Left_dXdY = dXdY_V1V2;
            LeftX  = (float)V1->x;
            RightX = (float)V1->x;
            DrawRenderMode(y1i, y2i,RGB, RenderMode);
        }
        if (y2i<y3i)
        {
            Left_dXdY = dXdY_V2V3;
            LeftX = (float)V2->x;
            DrawRenderMode(y2i, y3i,RGB, RenderMode);
		}
    }
    else
    if (mid) // Positve
    {
        if (y1i==y2i)
        {
					Left_dXdY = dXdY_V1V3;
					Right_dXdY = dXdY_V2V3;
					LeftX  = (float)V1->x;
					RightX = (float)V2->x;
          DrawRenderMode(y1i, y3i,RGB, RenderMode);
					return;
        }
        /* Brauchen wir ja nur einmal Init */
        Left_dXdY = dXdY_V1V3;
        if (y1i<y2i)
        {
            Right_dXdY = dXdY_V1V2;
            LeftX = (float)V1->x; // gleiche Start X cor !!!
            RightX= (float)V1->x;
            DrawRenderMode(y1i, y2i,RGB, RenderMode);
				}
				if (y2i<y3i)
				{
            Right_dXdY = dXdY_V2V3;
            RightX     = (float)V2->x;
            DrawRenderMode(y2i, y3i,RGB, RenderMode);
        }
    }
}
// Verzweigt zur richtigen Zeichenroutine
inline void CBitMap::DrawRenderMode(int y1, int y2,int RGB,int RM)
{
	switch (RM)
	{
		case 0: case 1:
				DrawSolidSegment(y1,y2,RGB);
			break;
		case 2:
				RGB=(RGB>>1) & 0x007f7f7f;
				DrawAlphaSegment(y1,y2,RGB);
			break;
		case 3:
				RGB=RGB & 0x00fefeff;
				DrawAdditiveSegment(y1,y2,RGB);
			break;
	}
}

// Zeichnet eine Solid Linie .....
inline void CBitMap::DrawSolidSegment(int y1, int y2,int RGB)
{
    // WORKING VERSION In FIXED POINT
    signed int x1, x2, y;

    for (y=y1;y<y2;y++)
    {

        /*eigene inline function schreiben !*/
        x1 =(int) ceil (LeftX);   // Subpixel Accuracy fr Poly-Aussenseiten links  !
        x2 =(int) ceil (RightX);  // Subpixel Accuarcy fr Poly-Aussenseiten rechts !

//        unsigned int * pTriangle = pPolyDest + x1;

//        int width;

        if (x1<x2)
        {
//            width = x2-x1;

//            _asm mov edi, pTriangle // ist cool, weil vc++ das uebernehmen hat
//            _asm mov ecx, width
//            _asm mov eax, RGB
//            _asm cld
//            _asm rep stosd
        }

        LeftX+=Left_dXdY;
        RightX+=Right_dXdY;
        pPolyDest+=Width + Pitch;  // Eine Zeile tiefer addieren !
    }
}


// Zeichnet eine AlphaHalf Linie .....(RGB vorher anpassen!)
inline void CBitMap::DrawAlphaSegment(int y1, int y2,int RGB)
{
    // WORKING VERSION In FIXED POINT
    signed int x1, x2, y;


    for (y=y1;y<y2;y++)
    {

        /*eigene inline function schreiben !*/
        x1 =(int) ceil (LeftX);   // Subpixel Accuracy fr Poly-Aussenseiten links  !
        x2 =(int) ceil (RightX);  // Subpixel Accuarcy fr Poly-Aussenseiten rechts !

        unsigned int * pTriangle = pPolyDest + x1;

        for (int z=x1;z<x2;z++)
        {
            int Alpha1 = *pTriangle >> 1;
            Alpha1 = Alpha1 & 0x007f7f7f;
            *pTriangle = Alpha1 + RGB;
            pTriangle++;
        }

        LeftX+=Left_dXdY;
        RightX+=Right_dXdY;
        pPolyDest+=Width + Pitch;  // Eine Zeile tiefer addieren !
    }
}
// Zeichnet eine AlphaAdd Linie .....
inline void CBitMap::DrawAdditiveSegment(int y1, int y2,int RGB)
{
    // WORKING VERSION In FIXED POINT
    signed int x1, x2, y;
		PIXEL Pix, Overflow;

    for (y=y1;y<y2;y++)
    {

        /*eigene inline function schreiben !*/
        x1 =(int) ceil (LeftX);   // Subpixel Accuracy fr Poly-Aussenseiten links  !
        x2 =(int) ceil (RightX);  // Subpixel Accuarcy fr Poly-Aussenseiten rechts !

        int* pTriangle = (int*)pPolyDest + (int)(x1);

        for (int z=x1;z<x2;z++)
        {
            Pix=(*pTriangle&(ADDMASK)) + RGB;

						Overflow=Pix &(ADDOVERMASK);
						Overflow=Overflow-(Overflow>>ADDMASKSHIFT);
            *pTriangle++=Pix | Overflow;
        }

        LeftX+=Left_dXdY;
        RightX+=Right_dXdY;
        pPolyDest+=Width+Pitch;  // Eine Zeile tiefer addieren !
    }
}

//Funct nur bei gleich grossen BitMaps und 32 BIT
void CBitMap::Blend(CBitMap *Source, CBitMap *Dest, int Alpha)	//Alpha 0..127 Source->Dest
{
	int SrcFact, DestFact, ySrcPix, yDestPix, tempPix, tempSrc, tempDst;
	PIXEL *pSrc, *pDest, *result;
	if (Alpha<0) Alpha=0;
	if (Alpha>127) Alpha=127;
	SrcFact=Alpha<<1;
	DestFact=(127-Alpha)<<1;
	pSrc=(PIXEL*)Source->getBitmap();
	pDest=(PIXEL*)Dest->getBitmap();
	result=(PIXEL*) BMap;
	for (int y=0;y<Source->getHeight();y++)
	{
		for (int x=0;x<Source->getWidth();x++)
		{
			tempPix=0;
			tempSrc=*pSrc;
			tempDst=*pDest;

			ySrcPix =(tempSrc & 0x00ff00ff) * SrcFact;
			yDestPix=(tempDst & 0x00ff00ff)* DestFact;
			tempPix=(((ySrcPix + yDestPix)>>8) & 0x00ff00ff);

			ySrcPix =((tempSrc & 0x0000ff00)) * SrcFact;
			yDestPix=((tempDst & 0x0000ff00))* DestFact;
			tempPix=tempPix | (((ySrcPix + yDestPix)>>8) & 0x0000ff00);

			pSrc++;
			pDest++;
			*result=tempPix;
			result++;
		}
		pSrc+=Source->getPitch();
		pDest+=Dest->getPitch();
		result+=Pitch;
	}
}
/////////////////////////////////////////////////////////////////////////////
void CBitMap::BlendPixel(CBitMap *Source, CBitMap *Dest,CBitMap* Mask, unsigned int Alpha)
{
	PIXEL *pSrc, *pDest, *pMask,*pResult;
	pSrc=Source->getBitmap();
	pDest=Dest->getBitmap();
	pMask=Mask->getBitmap();
	pResult= BMap;
	for (int y=0;y<Source->getHeight();y++)
	{
		for (int x=0;x<Source->getWidth();x++)
		{
			if ((*pMask&0xff)<Alpha)
				*pResult = *pSrc;
			else
				*pResult = *pDest;
			pResult++;
			pMask++;
			pSrc++;
			pDest++;
		}
		pSrc+=Source->getPitch();
		pDest+=Dest->getPitch();
		pMask+=Mask->getPitch();
		pResult+=Pitch;
	}
}
/////////////////////////////////////////////////////////////////////////////
void CBitMap::LensFlare(CBitMap *Src, int LX, int LY, int sizeX, int sizeY)
{
	int CenterX = Width/2;
	int CenterY = Height/2;

	int distX = LX - CenterX;
	int distY = LY - CenterY;

	float xco = (float)(distX)/4;
	float yco = (float)(distY)/4;

	LX-=sizeX/2;
	LY-=sizeY/2;

	Src->BltAdd(0*sizeX,0,sizeX,sizeY,this,LX,LY);
	Src->BltAdd(1*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*8)),(int)(LY-(yco*8)));
	Src->BltAdd(2*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*2)),(int)(LY-(yco*2)));
	Src->BltAdd(3*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*6)),(int)(LY-(yco*6)));
	Src->BltAdd(4*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*3)),(int)(LY-(yco*3)));
	Src->BltAdd(5*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*7)),(int)(LY-(yco*7)));
	Src->BltAdd(6*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*5)),(int)(LY-(yco*5)));
	Src->BltAdd(7*sizeX,0,sizeX,sizeY,this,(int)(LX-(xco*1)),(int)(LY-(yco*1)));
}

///////////////////////////////////////////////////////////////////////////
// Diese Methode Negiert einfach den Bildinhalt ......
///////////////////////////////////////////////////////////////////////////
void CBitMap::XorPattern()
{

	int Lenght    = Width;
	int Hoehe     = Height;
	PIXEL * pBuffer = BMap;
	int Pitch     = getPitch();


	for (int y=0;y<Hoehe;y++)
	{
		for (int x = 0 ; x < Lenght ; x ++)
		{
			*pBuffer = *pBuffer ^ 0x00ffffff ;
			pBuffer++;
		}
	pBuffer+=Pitch;
	}



}
// *************** Line Algorithms *************************
void CBitMap::Line(int x1, int y1, int x2, int y2, int Col)	// A simple Line in a static Color.. non transparent
{
	int dx, dy,i,y,x, dir, temp, totalWidth, offset;

	int a=(Col & 0xff000000) >> 24 ;
	int r=(Col & 0x00ff0000) >> 16 ;
	int g=(Col & 0x0000ff00) >> 8;
	int b=(Col & 0x000000ff) ;
	PIXEL pixCol=((a<<ASHIFT) & AMASK) | ((r<<RSHIFT)& RMASK) | ((g<<GSHIFT)& GMASK) | ((b>>BSHIFT)& BMASK) ;

	dx = x2-x1;
	dy = y2-y1;
	totalWidth=Pitch+Width;
	if (ABS(dx)>ABS(dy))
	{
		if (dx<0)				// Über die X-Achse laufen
		{
			temp=x2;		x2=x1;		x1=temp;	//SWAP them
			temp=y2;		y2=y1;		y1=temp;	//SWAP them
			dx = x2-x1;
			dy = y2-y1;
		}
		if (dy>0)
		{
			dir=totalWidth;
		}
		else
		{
			dir=-totalWidth;
			dy=-dy;
		}
		i=dx;
		y=y1;
		dx=dx<<1;dy=dy<<1;
		offset=x1+y1*totalWidth;
		for (x=x1;x<x2+1;x++)
		{
			BMap[offset]=pixCol;
			offset++;
			i=i-dy;
			if (i<0)
			{	i+=dx;	offset+=dir;	}
		}
	}
	else
	{
		if (dy<0)				// Über die Y-Achse laufen
		{
			temp=x2;		x2=x1;		x1=temp;	//SWAP them
			temp=y2;		y2=y1;		y1=temp;	//SWAP them
			dx = x2-x1;
			dy = y2-y1;
		}
		if (dx>0)
		{
			dir=1;
		}
		else
		{
			dir=-1;
			dx=-dx;
		}
		i=dy;
		x=x1;
		dx=dx<<1;dy=dy<<1;
		offset=x1+y1*totalWidth;
		for (y=y1;y<y2+1;y++)
		{
			BMap[offset]=pixCol;
			offset+=totalWidth;
			i=i-dx;
			if (i<0)
			{	i+=dy;	offset+=dir;		}
		}
	}
}
void CBitMap::Line(int x1, int y1, int x2, int y2, int col1, int col2)
{
	int dx, dy,i,y,x, dir, temp, col, offset, totalWidth;
	int ra,ga,ba, dr,dg,db,r=0,g=0,b=0;
	dx = x2-x1;
	dy = y2-y1;
	totalWidth =(Pitch + Width);
	if ((dx==0)&&(dy==0))
	{
		BMap[x1+y1*totalWidth]=col1;
		return;
	}
	if (ABS(dx)>ABS(dy))
	{
		if (dx<0)				// Über die X-Achse laufen
		{
			temp=x2;		x2=x1;		x1=temp;	//SWAP them
			temp=y2;		y2=y1;		y1=temp;	//SWAP them
			temp=col1;	col1=col2;col2=temp;
			dx = -dx;//x2-x1;
			dy = -dy;// y2-y1;
		}
		dr=(col2&0xff0000)-(col1&0xff0000);
		dg=(col2&0x00ff00)-(col1&0x00ff00);
		db=(col2&0x0000ff)-(col1&0x0000ff);
		if (dr<0) ra=(-1)<<16;else ra=1<<16;
		if (dg<0) ga=(-1)<<8 ;else ga=1<<8;
		if (db<0) ba=-1;else ba=1;
		dr=ABS(dr)>>15;
		dg=ABS(dg)>>7;
		db=ABS(db)<<1;
		if ((db>dg)&&(db>dr))		//Blau steigt am meisten
		{
			temp=db;	db=dr;	dr=temp;
			temp=b;		b=r;		r=temp;
			temp=ba;	ba=ra;	ra=temp;
		}else
		{	if (dg>dr) //gruen steigt am meisten
			{
				temp=dg;	dg=dr;	dr=temp;
				temp=g;		g=r;		r=temp;
				temp=ga;	ga=ra;	ra=temp;
			}
		}
		col=col1;
		if (dy>0)
		{			dir=totalWidth;		}
		else
		{		dir=-totalWidth; 	dy=-dy;	}
		i=dx;
		r=dx;		g=dr;		b=dr;
		dx=dx<<1;dy=dy<<1;				//Ausserhalb der schleife mit 2 Multiplizieren
		offset=x1+y1*(totalWidth);// Offset berechnen
		for (x=x2-x1;!(x<0);x--)
		{
			BMap[offset]=col;
			offset++;
			i=i-dy;				//	ySteigung
			if (i<0)	 {	i+=dx;	offset+=dir;	}
			r-=dr;				//	R-Wert
			while (r<0)
			{
				r+=dx;	col+=ra;
				g-=dg;				//	G-wert
				b-=db;				//	B-Wert
				while (g<0){	g+=dr;	col+=ga;		}
				while (b<0){	b+=dr;	col+=ba;		}
			}
		}
	}
	else
	{
		if (dy<0)				// Über die Y-Achse laufen
		{
			temp=x2;		x2=x1;		x1=temp;	//SWAP them
			temp=y2;		y2=y1;		y1=temp;	//SWAP them
			temp=col1;	col1=col2;col2=temp;
			dx = -dx ;//x2-x1;
			dy = -dy; //y2-y1;
		}
		dr=(col2&0xff0000)-(col1&0xff0000);
		dg=(col2&0x00ff00)-(col1&0x00ff00);
		db=(col2&0x0000ff)-(col1&0x0000ff);
		if (dr<0) ra=(-1)<<16;else ra=1<<16;
		if (dg<0) ga=(-1)<<8 ;else ga=1<<8;
		if (db<0) ba=-1;else ba=1;
		dr=ABS(dr)>>15;
		dg=ABS(dg)>>7;
		db=ABS(db)<<1;
		if ((db>dg)&&(db>dr))		//Blau steigt am meisten
		{
			temp=db;	db=dr;	dr=temp;
			temp=b;		b=r;		r=temp;
			temp=ba;	ba=ra;	ra=temp;
		}else
		{	if (dg>dr) //gruen steigt am meisten
			{
				temp=dg;	dg=dr;	dr=temp;
				temp=g;		g=r;		r=temp;
				temp=ga;	ga=ra;	ra=temp;
			}
		}
		col=col1;
		if (dx>0)
		{		dir=1;	}
		else
		{		dir=-1; 	dx=-dx;		}
		i=dy;
		r=dy;		g=dr;		b=dr;
		dx=dx<<1;dy=dy<<1;
		offset=x1+y1*(totalWidth);
		for (y=y2-y1;!(y<0);y--)
		{
			BMap[offset]=col;
			offset+=totalWidth;
			i=i-dx;
			if (i<0)		{	i+=dy;	offset+=dir;	}
			r-=dr;				//	R-Wert
			while (r<0)
			{
				r+=dy;	col+=ra;
				g-=dg;				//	G-wert
				b-=db;				//	B-Wert
				while (g<0)	{	g+=dr;	col+=ga;}
				while (b<0)	{	b+=dr;	col+=ba;}
			}
		}
	}
}
void CBitMap::LineAdd(int x1, int y1, int x2, int y2, int col1, int col2)
{
	int dx, dy,i,y,x, dir, temp, col, offset, totalWidth;
	int ra,ga,ba, dr,dg,db,r=0,g=0,b=0;
	dx = x2-x1;
	dy = y2-y1;
	totalWidth =(Pitch + Width);
	if ((dx==0)&&(dy==0))
	{
		BMap[x1+y1*totalWidth]=col1;
		return;
	}
	if (ABS(dx)>ABS(dy))
	{
		if (dx<0)				// Über die X-Achse laufen
		{
			temp=x2;		x2=x1;		x1=temp;	//SWAP them
			temp=y2;		y2=y1;		y1=temp;	//SWAP them
			temp=col1;	col1=col2;col2=temp;
			dx = -dx;//x2-x1;
			dy = -dy;// y2-y1;
		}
		dr=(col2&0xff0000)-(col1&0xff0000);
		dg=(col2&0x00ff00)-(col1&0x00ff00);
		db=(col2&0x0000ff)-(col1&0x0000ff);
		if (dr<0) ra=(-1)<<16;else ra=1<<16;
		if (dg<0) ga=(-1)<<8 ;else ga=1<<8;
		if (db<0) ba=-1;else ba=1;
		dr=ABS(dr)>>15;
		dg=ABS(dg)>>7;
		db=ABS(db)<<1;
		if ((db>dg)&&(db>dr))		//Blau steigt am meisten
		{
			temp=db;	db=dr;	dr=temp;
			temp=b;		b=r;		r=temp;
			temp=ba;	ba=ra;	ra=temp;
		}else
		{	if (dg>dr) //gruen steigt am meisten
			{
				temp=dg;	dg=dr;	dr=temp;
				temp=g;		g=r;		r=temp;
				temp=ga;	ga=ra;	ra=temp;
			}
		}
		col=col1;
		if (dy>0)
		{			dir=totalWidth;		}
		else
		{		dir=-totalWidth; 	dy=-dy;	}
		i=dx;
		r=dx;		g=dr;		b=dr;
		dx=dx<<1;dy=dy<<1;				//Ausserhalb der schleife mit 2 Multiplizieren
		offset=x1+y1*(totalWidth);// Offset berechnen
		for (x=x2-x1;!(x<0);x--)
		{
      int Pix=(BMap[offset]&(ADDMASK)) + (col & ADDMASK);
			int	Overflow=Pix &(ADDOVERMASK);
			Overflow=Overflow-(Overflow>>ADDMASKSHIFT);
      BMap[offset]=Pix | Overflow;

			offset++;
			i=i-dy;				//	ySteigung
			if (i<0)	 {	i+=dx;	offset+=dir;	}
			r-=dr;				//	R-Wert
			while (r<0)
			{
				r+=dx;	col+=ra;
				g-=dg;				//	G-wert
				b-=db;				//	B-Wert
				while (g<0){	g+=dr;	col+=ga;		}
				while (b<0){	b+=dr;	col+=ba;		}
			}
		}
	}
	else
	{
		if (dy<0)				// Über die Y-Achse laufen
		{
			temp=x2;		x2=x1;		x1=temp;	//SWAP them
			temp=y2;		y2=y1;		y1=temp;	//SWAP them
			temp=col1;	col1=col2;col2=temp;
			dx = -dx ;//x2-x1;
			dy = -dy; //y2-y1;
		}
		dr=(col2&0xff0000)-(col1&0xff0000);
		dg=(col2&0x00ff00)-(col1&0x00ff00);
		db=(col2&0x0000ff)-(col1&0x0000ff);
		if (dr<0) ra=(-1)<<16;else ra=1<<16;
		if (dg<0) ga=(-1)<<8 ;else ga=1<<8;
		if (db<0) ba=-1;else ba=1;
		dr=ABS(dr)>>15;
		dg=ABS(dg)>>7;
		db=ABS(db)<<1;
		if ((db>dg)&&(db>dr))		//Blau steigt am meisten
		{
			temp=db;	db=dr;	dr=temp;
			temp=b;		b=r;		r=temp;
			temp=ba;	ba=ra;	ra=temp;
		}else
		{	if (dg>dr) //gruen steigt am meisten
			{
				temp=dg;	dg=dr;	dr=temp;
				temp=g;		g=r;		r=temp;
				temp=ga;	ga=ra;	ra=temp;
			}
		}
		col=col1;
		if (dx>0)
		{		dir=1;	}
		else
		{		dir=-1; 	dx=-dx;		}
		i=dy;
		r=dy;		g=dr;		b=dr;
		dx=dx<<1;dy=dy<<1;
		offset=x1+y1*(totalWidth);
		for (y=y2-y1;!(y<0);y--)
		{
      int Pix=(BMap[offset]&(ADDMASK)) + (col&ADDMASK);
			int	Overflow=Pix &(ADDOVERMASK);
			Overflow=Overflow-(Overflow>>ADDMASKSHIFT);
      BMap[offset]=Pix | Overflow;

			offset+=totalWidth;
			i=i-dx;
			if (i<0)		{	i+=dy;	offset+=dir;	}
			r-=dr;				//	R-Wert
			while (r<0)
			{
				r+=dy;	col+=ra;
				g-=dg;				//	G-wert
				b-=db;				//	B-Wert
				while (g<0)	{	g+=dr;	col+=ga;}
				while (b<0)	{	b+=dr;	col+=ba;}
			}
		}
	}
}
// TextureMapping

// Malt eine Textuierte waagerechte Line
void CBitMap::LineTxt(int x1,int y1,int Wid, CBitMap* Source,int xt1,int yt1,int xt2,int yt2)
{
	PIXEL* SrcPointer;
	int SrcWidth, SrcOffset;

	int Offset=y1*(Width+Pitch) + x1;
	int dx,dy,xOff,yOff;
	int ix,iy,xl,yl;

	SrcPointer=Source->getBitmap();
	SrcWidth	=Source->getWidth()+Source->getPitch();
	xOff=0;yOff=0;
	dx=xt2-xt1;
	dy=yt2-yt1;
	if (dx<0) xOff=-1;
	if (dx>0) xOff= 1;
	if (dy<0) yOff=-SrcWidth;
	if (dy>0) yOff= SrcWidth;
	dx=ABS(dx);dy=ABS(dy);
	if (Wid<0)
	{
		ix=-Wid;iy=-Wid;
		xl=xt1;yl=yt1;
		SrcOffset=xl+yl*SrcWidth;
		for (int loop=-Wid;loop>0;loop--)
		{
			iy-=dy;
			ix-=dx;
			while(ix<0)
			{
				ix-=Wid;
				SrcOffset+=xOff;
			}
			while(iy<0)
			{
				iy-=Wid;
				SrcOffset+=yOff;
			}
			BMap[Offset--]=SrcPointer[SrcOffset];
		}
	}else{
		ix=Wid;iy=Wid;
		xl=xt1;yl=yt1;
		SrcOffset=xl+yl*SrcWidth;
		for (int loop=Wid;loop>0;loop--)
		{
			iy-=dy;
			ix-=dx;
			while(ix<0)
			{
				ix+=Wid;
				SrcOffset+=xOff;
			}
			while(iy<0)
			{
				iy+=Wid;
				SrcOffset+=yOff;
			}
			BMap[Offset++]=SrcPointer[SrcOffset];
		}

	}
}
void CBitMap::PolyTxT(Point* vertex, int n, CBitMap* Texture)
{
	int Low,High, indexLow, indexHigh;
	Low=vertex[0].y;
	High=vertex[0].y;
	indexLow=0;
	indexHigh=0;
	for (int index=1;index<=n; index++)
	{
		if (vertex[index].y<Low)
		{		indexLow=index; Low=vertex[index].y	;	}
		if (vertex[index].y>High)
		{		indexHigh=index; High=vertex[index].y	;	}
	}

	int NewLeftEdge, LeftEdge, xlL, dxL, dyL, yTargetL, LeftDir, iL, duL,dvL, iuL, ivL, DiruL, DirvL,ulL,vlL;
	LeftEdge=indexLow-1;										//Naechster Punkt nach Links...
	if (LeftEdge<0) LeftEdge=n;							//Wrappen
	xlL=vertex[indexLow].x;									//StartPunkt
	ulL=vertex[indexLow].u;									//StartPunkt
	vlL=vertex[indexLow].v;									//StartPunkt
	dxL=vertex[LeftEdge].x - vertex[indexLow].x;// DX on LeftEdge
	duL=vertex[LeftEdge].u - vertex[indexLow].u;// DU on LeftEdge
	dvL=vertex[LeftEdge].v - vertex[indexLow].v;// DV on LeftEdge
	dyL=vertex[LeftEdge].y - vertex[indexLow].y;// DY on LeftEdge
	yTargetL=vertex[LeftEdge].y ;						//Here is the next vertexChange

	if (dxL>0)	LeftDir=1;else { LeftDir=-1;dxL=-dxL;}				//stepping to the left or right ?
	if (duL>0)	DiruL=1;else { DiruL=-1;duL=-duL;}						//stepping to the left or right ?
	if (dvL>0)	DirvL=1;else { DirvL=-1;dvL=-dvL;}						//stepping to the left or right ?
	iL=dyL;																	//SteigungsWert...
	iuL=dyL;
	ivL=dyL;

	int NewRightEdge, RightEdge, xlR, dxR, dyR, yTargetR, RightDir, iR, duR,dvR, iuR,ivR,DiruR,DirvR,ulR,vlR;
	RightEdge=indexLow+1;										//Naechster Punkt nach Links...
	if (RightEdge>n) RightEdge=0;							//Wrappen
	xlR=vertex[indexLow].x;									//StartPunkt  XCoord
	ulR=vertex[indexLow].u;									//StartPunkt	Texture U Coord
	vlR=vertex[indexLow].v;									//StartPunkt	Texture V Coord
	dxR=vertex[RightEdge].x - vertex[indexLow].x;// DX on LeftEdge
	duR=vertex[RightEdge].u - vertex[indexLow].u;// DU on LeftEdge
	dvR=vertex[RightEdge].v - vertex[indexLow].v;// DV on LeftEdge
	dyR=vertex[RightEdge].y - vertex[indexLow].y;// DY on LeftEdge
	yTargetR=vertex[RightEdge].y ;						//Here is the next vertexChange

	if (dxR>0) RightDir=1;else { RightDir=-1;dxR=-dxR;}				//stepping to the left or right ?
	if (duR>0) DiruR=1;else { DiruR=-1;duR=-duR;}				//stepping to the left or right ?
	if (dvR>0) DirvR=1;else { DirvR=-1;dvR=-dvR;}				//stepping to the left or right ?
	iR=dyR;																	//SteigungsWert...
	iuR=dyR;																	//SteigungsWert...
	ivR=dyR;																	//SteigungsWert...

	for (int yl=vertex[indexLow].y; yl<vertex[indexHigh].y; yl++)
	{
		//++++++++++++++++++++++ Left Edge tracing +++++++++++++++++++++++
		if (yl==yTargetL)
		{
			NewLeftEdge=LeftEdge-1;
			if (NewLeftEdge<0) NewLeftEdge=n;//Wrappen
			xlL=vertex[LeftEdge].x;									//StartPunkt
			ulL=vertex[LeftEdge].u;									//StartPunkt
			vlL=vertex[LeftEdge].v;									//StartPunkt
			dxL=vertex[NewLeftEdge].x - vertex[LeftEdge].x;
			duL=vertex[NewLeftEdge].u - vertex[LeftEdge].u;
			dvL=vertex[NewLeftEdge].v - vertex[LeftEdge].v;
			dyL=vertex[NewLeftEdge].y - vertex[LeftEdge].y;

			yTargetL=vertex[NewLeftEdge].y ;						//Here is the next vertexChange

			if (dxL>0)LeftDir=1;else{ LeftDir=-1;dxL=-dxL;}
			if (duL>0)	DiruL=1;else { DiruL=-1;duL=-duL;}
			if (dvL>0)	DirvL=1;else { DirvL=-1;dvL=-dvL;}
			LeftEdge=NewLeftEdge;
			iL=dyL;
			iuL=dyL;
			ivL=dyL;
		}
		iL-=dxL;
		while (iL<0){	iL+=dyL;	xlL+=LeftDir;	}
		iuL-=duL;
		while (iuL<0){	iuL+=dyL;	ulL+=DiruL;	}
		ivL-=dvL;
		while (ivL<0){	ivL+=dyL;	vlL+=DirvL;	}

// ++++++++++++++++++++++++++Right edge tracing ++++++++++++++++++++
		if (yl==yTargetR)
		{
			NewRightEdge=RightEdge+1;
			if (NewRightEdge>n) NewRightEdge=0;//Wrappen
			xlR=vertex[RightEdge].x;									//StartPunkt
			ulR=vertex[RightEdge].u;									//StartPunkt
			vlR=vertex[RightEdge].v;									//StartPunkt
			dxR=vertex[NewRightEdge].x - vertex[RightEdge].x;
			duR=vertex[NewRightEdge].u - vertex[RightEdge].u;
			dvR=vertex[NewRightEdge].v - vertex[RightEdge].v;
			dyR=vertex[NewRightEdge].y - vertex[RightEdge].y;

			yTargetR=vertex[NewRightEdge].y ;						//Here is the next vertexChange

			if (dxR>0)	RightDir=1;else { RightDir=-1;dxR=-dxR;}
			if (duR>0)	DiruR=1;else { DiruR=-1;duR=-duR;}
			if (dvR>0)	DirvR=1;else { DirvR=-1;dvR=-dvR;}
			RightEdge=NewRightEdge;
			iR=dyR;
			iuR=dyR;
			ivR=dyR;
		}
		iR-=dxR;
		while (iR<0){	iR+=dyR;	xlR+=RightDir;	}
		iuR-=duR;
		while (iuR<0){	iuR+=dyR;	ulR+=DiruR;	}
		ivR-=dvR;
		while (ivR<0){	ivR+=dyR;	vlR+=DirvR;	}

		LineTxt(xlL,yl,xlR-xlL,Texture,ulL,vlL,ulR,vlR);
	}
}

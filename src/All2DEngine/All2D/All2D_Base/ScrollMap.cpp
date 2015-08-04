// ScrollMap.cpp: Implementierung der Klasse ScrollMap.
//
//////////////////////////////////////////////////////////////////////

#include "ScrollMap.h"
#include <math.h>
//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

ScrollMap::ScrollMap()
{
	ptrMapData=NULL;
	ptScrollOffset=Point(0,0);
	setBlitMode(IMAGE_BLTMODE_FAST);
}

ScrollMap::~ScrollMap()
{

}

bool ScrollMap::loadTiles(string fileName)
{
	return ImageText::loadFont(fileName);
}

void ScrollMap::initTiles(int tileWidth, int tileHeight, int tilesPerRow)
{
	ImageText::FontInit(tileWidth, tileHeight,tilesPerRow);
}

void ScrollMap::setScrollOffset(int x, int y)
{
	ptScrollOffset.x=x;
	ptScrollOffset.y=y;
}

bool ScrollMap::loadMap(string strFileName)
{
	FILE *fp;

	fp = fopen(strFileName.c_str(), "rb");
	if(fp == NULL) 
		return false;

	fread(&iMapWidth, sizeof(int), 1, fp);
	fread(&iMapHeight, sizeof(int), 1, fp);
	
	initMap(iMapWidth, iMapHeight);

	for(int i=0; i<iMapWidth*iMapHeight; i++) 
	{
		int readInt=0;
		fread(&readInt,sizeof(int),1,fp);
		if (feof(fp)!=0)
			break;
		ptrMapData[i]=readInt+32;
	}

	fclose(fp);

	return true;
}

bool ScrollMap::paint(Image& backBuffer)
{
	int tileWidth=ImageText::getFontWidth();
	int tileHeight=ImageText::getFontHeight();

	Point ptScrOffset(0,0);	// this is the PixelOffset, for blitting the Tiles
	Point ptMapOffset(0,0);	// this is the MapOffset for reading the Map..

	// Calculating the tileArea of Backbuffer..for checking ScrollOffset

	if (ptScrollOffset.x>iMapWidth*ImageText::getFontWidth()-backBuffer.getWidth())
		ptScrollOffset.x=iMapWidth*ImageText::getFontWidth()-backBuffer.getWidth();

	if (ptScrollOffset.x<0)
		ptScrollOffset.x=0;

	if (ptScrollOffset.y>iMapHeight*ImageText::getFontHeight()-backBuffer.getHeight())
		ptScrollOffset.y=iMapHeight*ImageText::getFontHeight()-backBuffer.getHeight();

	if (ptScrollOffset.y<0)
		ptScrollOffset.y=0;

	ptMapOffset.x=ptScrollOffset.x/tileWidth;
	ptMapOffset.y=ptScrollOffset.y/tileHeight;
	ptScrOffset.x=ptScrollOffset.x%tileWidth;
	ptScrOffset.y=ptScrollOffset.y%tileHeight;

	for (int x=0;x<ceil((float)backBuffer.getWidth()/tileWidth)+1;x++)
		for (int y=0;y<ceil((float)backBuffer.getHeight()/tileHeight)+1;y++)
		{
			char cTileNumber=(char)ptrMapData[x+ptMapOffset.x+(y+ptMapOffset.y)*iMapWidth];
			if (cTileNumber!=32)
				ImageText::WriteChar(backBuffer,x*tileWidth-ptScrOffset.x,y*tileHeight-ptScrOffset.y,cTileNumber,iBlitMode);
		}	
	return true;
}

Point ScrollMap::getScrollOffset()
{
	return ptScrollOffset;
}

void ScrollMap::initMap(int mapWidth, int mapHeight, int mapFill)
{
	if (ptrMapData!=NULL)
		delete[] ptrMapData;
	
	iMapWidth=mapWidth;
	iMapHeight=mapHeight;
	
	ptrMapData=new int[iMapWidth*iMapHeight];
	for (int x=0;x<iMapWidth*iMapHeight;x++)
		ptrMapData[x]=mapFill;
}

// ScrollMap.h: Schnittstelle für die Klasse ScrollMap.
// A Scrollmap is just a tilebased Screen which is scrollable.
// The Scrolling will be set in the
// setScrollOffset(int x, int y) Method
// in the
// initTiles(int w, int h, int no) method it gives some Infos
// about the Tiles
// loadTiles(string strFileName) will load the tiles
// loadMap(string strFileName) will load the MapData
// paint(Image *backBuffer) will paint with actual scrolloffset
//////////////////////////////////////////////////////////////////////
#pragma once
#include "ImageText.h"
#include "../All2D_Base/xElement.h"
#include "../../UTILS/Point.h"	// Hinzugefügt von der Klassenansicht

class ScrollMap :
								private virtual ImageText,
								public virtual xElement
{
public:
	int getBlitMode(){	return iBlitMode;};
	void setBlitMode(int iBltMd){	iBlitMode=iBltMd;};
	void initMap(int mapWidth, int mapHeight, int mapFill=1);
	Point getScrollOffset();
	bool paint(Image& backBuffer);
	bool loadMap(string strFileName);
	void setScrollOffset(int x, int y);
	void initTiles(int tileWidth, int tileHeight, int tilesPerRow);
	bool loadTiles(string fileName);
	ScrollMap();
	virtual ~ScrollMap();
protected:
	Point ptScrollOffset;
	int iMapWidth, iMapHeight;
private:
	int iBlitMode;
	int* ptrMapData;
};

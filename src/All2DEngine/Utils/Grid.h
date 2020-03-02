// Grid.h: Schnittstelle für die Klasse Grid.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "Rect.h"
#include "Point.h"	// Hinzugefügt von der Klassenansicht
#include "../All2D/All2D_Base/Image.h"

class Grid : public Rect
{
public:
	Point getCoords(int x,int y);
	Point getGridIndex(int x,int y);
	int getGridPosition(int x, int y);
	void initGrid(int offX=0, int offY=0, int sizeX=10, int sizeY=10);
	Point gridPosition(int x, int y, bool snapFreeArea=true);		//snapAreaFree=true bedeutet, das das mittlere Drittel zwischen zwei GridLines SnapFree ist..
	Grid();
	virtual ~Grid();

protected:
	int xSize;
	int ySize;
	int xOffset;
	int yOffset;
};

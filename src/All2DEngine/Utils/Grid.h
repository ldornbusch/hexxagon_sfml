// Grid.h: Schnittstelle für die Klasse Grid.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRID_H__5F707461_4477_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_GRID_H__5F707461_4477_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Rect.h"
#include "POINT.H"	// Hinzugefügt von der Klassenansicht
#include "../All2D/All2D_Base/IMAGE.h"

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

#endif // !defined(AFX_GRID_H__5F707461_4477_11D5_B046_00E098802DF2__INCLUDED_)

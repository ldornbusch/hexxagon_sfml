// Grid.cpp: Implementierung der Klasse Grid.
//
//////////////////////////////////////////////////////////////////////

#include "Grid.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Grid::Grid() : Rect()
{
	initGrid (1,1,1,1);
}

Grid::~Grid()
{

}
// gibt den naechsten Punkt im Grid zurueck..
// bool snapFreeArea=false laesst das mittlere Drittel 
// zwischen zwei GridLines ohne snap
Point Grid::gridPosition(int x, int y, bool snapFreeArea)
{
	Point	retVal;
	retVal.x=x;
	retVal.y=y;
	if (isInside(x,y))
	{
		int wx=x-x1;					// relativ zum GridPosition transformieren..
		int wy=y-y1;
		wx-=xOffset;
		wy-=yOffset;
		int roundX=wx%xSize;		// roundXist die Anzahl derPixel in der Zelle:zB: 85 in einem 10er Grid ist 5 (bei Offset 0)
		retVal.x=wx / xSize;		// int-Division:85/10=8
		if (snapFreeArea && roundX>xSize/3 && roundX<(2*xSize)/3 )	// es wird nur gesnaped, wenn die Position im vorderen, oder hinteren Drittel liegt..
		{
			retVal.x=x;	// Kein Snap!
		} else {
			if (roundX>=(snapFreeArea? 2*xSize/3 : xSize/2 ))
				retVal.x++;					//evt. Aufrunden
			
			retVal.x*=xSize;
			retVal.x+=xOffset;
			retVal.x+=x1;
		}

		int roundY=wy%ySize;
		retVal.y=wy / ySize;		// int-Division:85/10=8
		if (snapFreeArea && roundY>ySize/3 && roundY<(2*ySize)/3 )	// es wird nur gesnaped, wenn die Position im vorderen, oder hinteren Drittel liegt..
		{
			retVal.y=y;	// Kein Snap!
		} else {
			if (roundY>=ySize/2)
				retVal.y++;					//evt. Aufrunden

			retVal.y*=ySize;
			retVal.y+=yOffset;
			retVal.y+=y1;
		}
	}
	return retVal;
}
// Initialisiert die Offsets und die Dimensionen des Grids
void Grid::initGrid(int offX, int offY, int sizeX, int sizeY)
{
	xSize=sizeX;
	ySize=sizeY;
	xOffset=offX;
	yOffset=offY;
}

// gibt die nummer der Grids wieder, also bei einem 10x10 Grid 
// kann die Nummer von 0-99 sein
// Sonderfall: wenn x/y nicht im Grid ist, gibt die Methode -1 zurück
int Grid::getGridPosition(int x, int y)
{
	int retVal=-1;	// 
	
	if (isInside(x,y))
	{
		int wx=x-x1;					// relativ zum GridPosition transformieren..
		int wy=y-y1;
		wx-=xOffset;
		wy-=yOffset;
		
		int gridX=wx/xSize;
		int gridY=wy/ySize;

		int cellsPerRow=x2/xSize;
		
		retVal= gridX + gridY * cellsPerRow;
	}

	return retVal;
}

// Diese Function gibt die Coordinaten in Grid einheiten zurueck
// zb: bei einem 10x10 px Grid liegt der Punkt 35/35 in den Indexes 3/3
Point Grid::getGridIndex(int x,int y)
{	
	Point retVal(-1,-1);
	if (isInside(x,y))
	{
		int wx=x-x1;					// relativ zum GridPosition transformieren..
		int wy=y-y1;
		wx-=xOffset;
		wy-=yOffset;
		
		retVal.x=wx/xSize;
		retVal.y=wy/ySize;
	}

	return retVal;
}

// Diese Funktion gibt zu dem Index ein KoordinatenPaar zurueck
// zb: bei 3/3 --> wird 30/30 zurueckgegeben, wenn jede Kachel 10x10 Px ist
Point Grid::getCoords(int iXIndex,int iYIndex)
{
	return Point (iXIndex*xSize+xOffset+Rect::x1
				 ,iYIndex*ySize+yOffset+Rect::y1);
}
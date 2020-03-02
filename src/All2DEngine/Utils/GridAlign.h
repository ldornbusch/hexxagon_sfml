// GridAlign.h: Schnittstelle für die Klasse GridAlign.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "Point.h"	// Hinzugefügt von der Klassenansicht

#include "Grid.h"

class GridAlign : public Grid
{
public:
	void setRightBorder(int iB);
	void setAlign(bool blnAlignRight=false);
	Point gridPosition(int length, int xc, int yc, bool snapIt=true, bool alignIt=true);
	void clearMap();
	void	setSize(int w, int h);

	GridAlign();
	virtual ~GridAlign();
private:
	int iRightBorder;
	void moveStripe(int col, int row, int len);
	int find(int len);
	void remove(int len);
	void allocPlace(int col, int row, int len, int val);
	int findNextFreePlace(int iRow,int iVal);
	bool	alignRight;
	int*	alignMap;
	int iWidth, iHeight;
	vector<Point*> vecCoords;	// hier werden die Coords gespeichert
	vector<int> vecLengths;		// hier die zugehörigen length..
};

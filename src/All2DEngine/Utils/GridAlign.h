// GridAlign.h: Schnittstelle für die Klasse GridAlign.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDALIGN_H__16DD38D7_3718_457D_A0D3_638C207F9E9A__INCLUDED_)
#define AFX_GRIDALIGN_H__16DD38D7_3718_457D_A0D3_638C207F9E9A__INCLUDED_

#include "POINT.H"	// Hinzugefügt von der Klassenansicht
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_GRIDALIGN_H__16DD38D7_3718_457D_A0D3_638C207F9E9A__INCLUDED_)
 
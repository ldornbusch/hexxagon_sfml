// Point.h: Schnittstelle für die Klasse Point.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT_H__D76B66B3_B09A_11D3_B8D2_0000E8699C86__INCLUDED_)
#define AFX_POINT_H__D76B66B3_B09A_11D3_B8D2_0000E8699C86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Point  
{
public:
	Point(int nx, int ny);
	Point(int nx, int ny, int nu, int nv);
	Point();
	~Point();
	int y;
	int x;
	int u;
	int v;
}; 

#endif // !defined(AFX_POINT_H__D76B66B3_B09A_11D3_B8D2_0000E8699C86__INCLUDED_)

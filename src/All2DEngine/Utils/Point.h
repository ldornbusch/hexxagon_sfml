// Point.h: Schnittstelle für die Klasse Point.
//
//////////////////////////////////////////////////////////////////////

#pragma once

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

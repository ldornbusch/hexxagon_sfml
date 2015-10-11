// Vector.h: Schnittstelle für die Klasse Vector.
//
// a small 2D-Vector
//////////////////////////////////////////////////////////////////////
#pragma once

#include "Point.h"
class Vector
{
public:
	static double distance(Vector a, Vector b);
	Vector(float x, float y);
	Vector(Point p);
	Vector();
	virtual ~Vector();
	float fX, fY;
	float normalize();
};

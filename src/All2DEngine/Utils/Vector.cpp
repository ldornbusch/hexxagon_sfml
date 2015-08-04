// Vector.cpp: Implementierung der Klasse Vector.
//
//////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Vector::Vector()
{

}
Vector::Vector(Point p)
{
	fX=p.x;
	fY=p.y;
}

Vector::Vector(float x, float y)
{
	fX=x;
	fY=y;
}

Vector::~Vector()
{

}
float Vector::normalize()
{
	return sqrt(fX*fX+fY*fY);
}

double Vector::distance(Vector a, Vector b)
{
	Vector tmp;
	tmp.fX=a.fX-b.fX;
	tmp.fY=a.fY-b.fY;
	return sqrt( (tmp.fX*tmp.fX) + (tmp.fY*tmp.fY) );
}

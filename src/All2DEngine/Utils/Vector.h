// Vector.h: Schnittstelle für die Klasse Vector.
//
// a small 2D-Vector
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__CB139024_68F9_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_VECTOR_H__CB139024_68F9_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_VECTOR_H__CB139024_68F9_11D5_B046_00E098802DF2__INCLUDED_)

// Line.h: Schnittstelle für die Klasse Line.
//
// This is the Representation of a 2D-VectorLine
// it is made from 2 Vectors,Place And Direction
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__CB139023_68F9_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_LINE_H__CB139023_68F9_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"

#define LINE2D_NO_INTERSECT	0x0000
#define LINE2D_INTERSECTION	0x0001
#define LINE2D_EQUAL			0x0002

class Line  
{
public:
	Line();
	Line(Vector ort, Vector dir);
	virtual ~Line();
	Vector	place, direction;
	int	intersect(Vector &HitPoint,float &thisFactor, float &secFactor, Line second);
private:
	int checkParallelIntersection(Vector &HitPoint, Line second);
};

#endif // !defined(AFX_LINE_H__CB139023_68F9_11D5_B046_00E098802DF2__INCLUDED_)

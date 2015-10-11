// Line.h: Schnittstelle für die Klasse Line.
//
// This is the Representation of a 2D-VectorLine
// it is made from 2 Vectors,Place And Direction
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"

//TODO create enum
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

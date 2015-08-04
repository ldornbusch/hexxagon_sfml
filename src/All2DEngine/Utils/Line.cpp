// Line.cpp: Implementierung der Klasse Line.
//
//////////////////////////////////////////////////////////////////////

#include "Line.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

Line::Line()
{

}

Line::Line(Vector ort, Vector dir)
{
	place=ort;
	direction=dir;
}

Line::~Line()
{

}

// returns if a intersection occurs
// and in the reference it gives the HitPoint, and the two scalars, 
// NOTE: a Intersection occurs even  if the Scalars are not in Range of 0..1 
// So check the 
int Line::intersect(Vector &HitPoint,float &thisFactor, float &secFactor, Line second)
{
	double probe, factor;
	thisFactor=-1;
	secFactor=-1;
	if (second.direction.fX==0)
	{
		probe=direction.fX ;// - (second.direction.fX/second.direction.fY)*direction.fY; // faellt ja weg, da fX=0 ist
		if (probe==0)
			return checkParallelIntersection(HitPoint, second);

		factor=	(second.place.fX - place.fX + 
						(second.direction.fX/second.direction.fY)*(place.fY-second.place.fY) ) / probe ;

		thisFactor=factor;
		secFactor=(place.fY - second.place.fY +factor * direction.fY)/second.direction.fY;
		
		HitPoint.fX=place.fX + factor * direction.fX;
		HitPoint.fY=place.fY + factor * direction.fY;

	} else {
	
		probe= direction.fY - (second.direction.fY/second.direction.fX)*direction.fX;
		if (probe==0)
			return checkParallelIntersection(HitPoint, second);

		factor=	(second.place.fY - place.fY + 
						(second.direction.fY/second.direction.fX)*(place.fX-second.place.fX)) / probe ;

		thisFactor=factor;
		secFactor=(place.fX - second.place.fX +factor * direction.fX)/second.direction.fX;

		HitPoint.fX=place.fX + factor * direction.fX;
		HitPoint.fY=place.fY + factor * direction.fY;
	}
	return LINE2D_INTERSECTION;	// Linien schneiden sich immer, es sei denn, sie sind paralell
}

int	Line::checkParallelIntersection(Vector &HitPoint, Line second)
{
	double probe;
	Vector diff;
	// erst Differenz-Vector berechnen, dann checken ob er paralell zur Steigung der geraden liegt
	diff.fX = second.place.fX - place.fX;
	diff.fY = second.place.fY - place.fY;
	
	if (diff.fX==0 && diff.fY==0)	// Beide Ortsvectoren gleich?
		return LINE2D_EQUAL;

	if (diff.fY==0)
	{
		probe=direction.fY -(diff.fY/diff.fX)*direction.fY ; 
		if (probe==0)
			return LINE2D_EQUAL;
	} else {

		probe=direction.fX -(diff.fX/diff.fY)*direction.fY ; 
		if (probe==0)
			return LINE2D_EQUAL;
	}
	return LINE2D_NO_INTERSECT;
}
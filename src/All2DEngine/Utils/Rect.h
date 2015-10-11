// Rect.h: Schnittstelle für die Klasse Rect.
//
//////////////////////////////////////////////////////////////////////

#pragma once
// Diese Coordinate wird als Standardwert benutzt, wenn eine Koordinate nicht gültig sein soll
#define RECT_INVALID	-66666
class Rect
{
public:
	bool clip(Rect & toClip);
	int getHeight();
	int getWidth();
	bool isInside(int x, int y);
	void setPosition(int x=RECT_INVALID, int y=RECT_INVALID, int w=RECT_INVALID, int h=RECT_INVALID);

	bool operator==(Rect sec);

	Rect(int x, int y=RECT_INVALID, int w=RECT_INVALID, int h=RECT_INVALID);
	Rect();
	virtual ~Rect();

	int x1;
	int y1;
	int x2;
	int y2;
};

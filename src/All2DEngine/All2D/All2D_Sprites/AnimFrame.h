// AnimFrame.h: Schnittstelle für die Klasse AnimFrame.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include "../All2D_Base/Image.h"
#include "../../UTILS/POINT.H"	// Hinzugefügt von der Klassenansicht

class AnimFrame : public Image
{
public:
	bool loadImage(string fileName);
	Point offset;
	int duration;
	AnimFrame();
	AnimFrame(int w, int h);
	virtual ~AnimFrame();

};

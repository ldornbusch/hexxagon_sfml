// AnimFrame.cpp: Implementierung der Klasse AnimFrame.
//
//////////////////////////////////////////////////////////////////////

#include "../All2D_System.h"
#include "AnimFrame.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

AnimFrame::AnimFrame(int w, int h) :Image(w,h)
{
	offset.x=0;
	offset.y=0;
	duration=1;
}

AnimFrame::AnimFrame()
{
	offset.x=0;
	offset.y=0;
	duration=1;
}

AnimFrame::~AnimFrame()
{

}

bool AnimFrame::loadImage(string fileName)
{
	return Image::loadImage(All2D_System::dataPath(fileName));
}

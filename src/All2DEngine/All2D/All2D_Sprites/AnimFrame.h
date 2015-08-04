// AnimFrame.h: Schnittstelle für die Klasse AnimFrame.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIMFRAME_H__D613F2E1_218B_11D5_B046_00E098802DF2__INCLUDED_)
#define AFX_ANIMFRAME_H__D613F2E1_218B_11D5_B046_00E098802DF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#endif // !defined(AFX_ANIMFRAME_H__D613F2E1_218B_11D5_B046_00E098802DF2__INCLUDED_)
